//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_BATH_FACTORY_H
#define MQDS_BATH_FACTORY_H

#include "MQDS/bath.h"
#include "MQDS/io.h"
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <functional>

namespace MQDS
{
    class BathFactory
    {
    public:
        using TCreateBathClass = std::function<std::unique_ptr<MQDS::Bath>()>;

        BathFactory() = default;
        virtual ~BathFactory() = default;

        static std::unique_ptr<MQDS::Bath>
        Create(IO & my_io) {
            if (auto it = bath_classes_().find(my_io.bath_potential()) ;
                    it !=  MQDS::BathFactory::bath_classes_().end())
            {
                return it->second();
            }
            std::cout << "didn't find " << my_io.bath_potential() << std::endl;
            return nullptr;
        }


        static bool
        Register(const std::string name, TCreateBathClass bathCreate) {
            if (auto it = bath_classes_().find(name) ;
                    it == bath_classes_().end())
            {
                bath_classes_()[name] = bathCreate;
                return true;
            }
            return false;
        }
        template <typename T>
        static bool
        Register(const std::string name) {
            if (auto it = bath_classes_().find(name) ;
                    it == bath_classes_().end())
            {
                bath_classes_()[name] = []() -> std::unique_ptr<MQDS::Bath> { return std::make_unique<T>();};
                return true;
            }
            return false;
        }

private:
        static std::map<std::string, TCreateBathClass>& bath_classes_(){
            static std::map<std::string, TCreateBathClass > b_classes;
            return b_classes;
        };
    };
};

#endif //MQDS_BATH_FACTORY_H
