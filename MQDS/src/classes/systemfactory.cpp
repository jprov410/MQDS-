//
// Created by Justin Provazza on 12/8/18.
//

#include "MQDS/systemfactory.h"
#include "MQDS/system.h"
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include <functional>

//std::map<std::string, MQDS::SystemFactory::TCreateSystemClass >&
//        MQDS::SystemFactory::system_classes_(){
//    static std::map<std::string, MQDS::SystemFactory::TCreateSystemClass > s_classes;
//    return s_classes;
//};


//bool MQDS::SystemFactory::Register(const std::string name, MQDS::SystemFactory::TCreateSystemClass sysCreate)
//{
//    if (auto it = MQDS::SystemFactory::system_classes_().find(name) ;
//            it == MQDS::SystemFactory::system_classes_().end())
//    {
//        MQDS::SystemFactory::system_classes_()[name] = sysCreate;
//        return true;
//    }
//    return false;
//}


//template <typename T>
//bool MQDS::SystemFactory::Register(const std::string name)
//{
//    if (auto it = MQDS::SystemFactory::system_classes_().find(name) ;
//            it == MQDS::SystemFactory::system_classes_().end())
//    {
//        MQDS::SystemFactory::system_classes_()[name]
//                = []() -> std::unique_ptr<MQDS::System>
//        { return std::make_unique<T>();};
//        return true;
//    }
//    return false;
//}

//std::unique_ptr<MQDS::System>
//MQDS::SystemFactory::Create(const std::string & class_name)
//{
//    //std::cout << MQDS::SystemFactory::system_classes_ << std::endl;
//    if (auto it = MQDS::SystemFactory::system_classes_().find(class_name) ;
//            it !=  MQDS::SystemFactory::system_classes_().end()) {
//        return it->second(); //Call Create Function
//    };
//    return nullptr;
//}
