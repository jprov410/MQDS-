//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_METHOD_FACTORY_H
#define MQDS_METHOD_FACTORY_H

#include "MQDS/method.h"
#include "MQDS/io.h"
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <functional>

namespace MQDS
{
    class MethodFactory {
    public:
        using TCreateMethodClass = std::function<std::unique_ptr<MQDS::Method>()>;

        MethodFactory() = default;
        virtual ~MethodFactory() = default;

        static std::unique_ptr<MQDS::Method>
        Create(IO & my_io) {
            if (auto it = method_classes_().find(my_io.method()) ;
                    it !=  MQDS::MethodFactory::method_classes_().end())
            {
                return it->second();
            }
            std::cout << "didn't find method type " << my_io.method() << std::endl;
            return nullptr;
        }


        static bool
        Register(const std::string name, TCreateMethodClass methCreate) {
            if (auto it = method_classes_().find(name) ;
                    it == method_classes_().end())
            {
                method_classes_()[name] = methCreate;
                return true;
            }
            return false;
        }
        template <typename T>
        static bool
        Register(const std::string name) {
            if (auto it = method_classes_().find(name) ;
                    it == method_classes_().end())
            {
                method_classes_()[name] = []() -> std::unique_ptr<MQDS::Method> { return std::make_unique<T>();};
                return true;
            }
            return false;
        }

private:
        static std::map<std::string, TCreateMethodClass>& method_classes_(){
            static std::map<std::string, TCreateMethodClass > m_classes;
            return m_classes;
        };
    };
};

#endif //MQDS_METHOD_FACTORY_H
