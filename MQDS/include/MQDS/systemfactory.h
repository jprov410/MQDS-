//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_SYSTEM_FACTORY_H
#define MQDS_SYSTEM_FACTORY_H

#include "MQDS/system.h"
#include "MQDS/io.h"
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <functional>

namespace MQDS
{
    class SystemFactory {
    public:
        using TCreateSystemClass = std::function<std::unique_ptr<MQDS::System>()>;

        SystemFactory() = default;
        virtual ~SystemFactory() = default;

        static std::unique_ptr<MQDS::System>
        Create(IO & my_io) {
            if (auto it = system_classes_().find(my_io.system_basis()) ;
                    it !=  MQDS::SystemFactory::system_classes_().end())
            {
                return it->second();
            }
            std::cout << "didn't find " << my_io.system_basis() << std::endl;
            return nullptr;
        }


        static bool
        Register(const std::string name, TCreateSystemClass sysCreate) {
            if (auto it = system_classes_().find(name) ;
                    it == system_classes_().end())
            {
                system_classes_()[name] = sysCreate;
                return true;
            }
            return false;
        }
        template <typename T>
        static bool
        Register(const std::string name) {
            if (auto it = system_classes_().find(name) ;
                    it == system_classes_().end())
            {
                system_classes_()[name] = []() -> std::unique_ptr<MQDS::System> { return std::make_unique<T>();};
                return true;
            }
            return false;
        }
private:
        static std::map<std::string, TCreateSystemClass> & system_classes_(){
            static std::map<std::string, TCreateSystemClass > s_classes;
            return s_classes;
        };
    };
};

#endif //MQDS_SYSTEM_FACTORY_H
