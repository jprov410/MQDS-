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
    class SystemFactory;
}

class MQDS::SystemFactory {
public:
    using TCreateSystemClass = std::function<std::unique_ptr<MQDS::System>()>;

    SystemFactory() = default;
    virtual ~SystemFactory() = default;


    //static bool
    //Register(const std::string name, TCreateSystemClass sysCreate);

    //template <typename T>
    //static bool
    //Register(const std::string name);



    //static std::unique_ptr<MQDS::System>
    //Create(const std::string & class_name)
    static std::unique_ptr<MQDS::System>
    Create(IO & my_io)
    {
        std::cout << "Made it into the SystemFactory::Create function"<< std::endl;

        if (auto it = system_classes_().find(my_io.system_basis()) ;
                it !=  MQDS::SystemFactory::system_classes_().end())
        {std::cout << "found  " << my_io.system_basis() << std::endl;
            return it->second();} //Call Create Function
        std::cout << "didn't find " << my_io.system_basis() << std::endl;

        return nullptr;
    }


    static bool
    Register(const std::string name, TCreateSystemClass sysCreate) {
        std::cout << name << "in register #1" << std::endl;
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
        std::cout << name << "In Register Number 2"<< std::endl;
        if (auto it = system_classes_().find(name) ;
                it == system_classes_().end())
        {
            system_classes_()[name] = []() -> std::unique_ptr<MQDS::System> { return std::make_unique<T>();};
            return true;
        }
        return false;
    }




//    static std::unique_ptr<MQDS::System>
//    Create(const std::string & class_name);

private:
    static std::map<std::string, TCreateSystemClass>& system_classes_(){
        static std::map<std::string, TCreateSystemClass > s_classes;
        std::cout << "made it into system_classes()" << std::endl;
        return s_classes;
    };
};


#endif //MQDS_SYSTEM_FACTORY_H
