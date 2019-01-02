//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_CALCULATION_FACTORY_H
#define MQDS_CALCULATION_FACTORY_H

#include "MQDS/calculation.h"
#include "MQDS/io.h"
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <functional>

namespace MQDS
{
    class CalculationFactory;
}

class MQDS::CalculationFactory {
public:
    using TCreateCalculationClass = std::function<std::unique_ptr<MQDS::Calculation>()>;

    CalculationFactory() = default;
    virtual ~CalculationFactory() = default;

    static std::unique_ptr<MQDS::Calculation>
    Create(IO & my_io) {
        if (auto it = calculation_classes_().find(my_io.calculation()) ;
                it !=  MQDS::CalculationFactory::calculation_classes_().end())
        {
            return it->second();
        }
        std::cout << "didn't find " << my_io.calculation() << std::endl;
        return nullptr;
    }
    
    static bool
    Register(const std::string name, TCreateCalculationClass calcCreate) {
        if (auto it = calculation_classes_().find(name) ;
                it == calculation_classes_().end())
       {
            calculation_classes_()[name] = calcCreate;
            return true;
        }
        return false;
    }
    template <typename T>
    static bool
    Register(const std::string name) {
        if (auto it = calculation_classes_().find(name) ;
                it == calculation_classes_().end())
        {
            calculation_classes_()[name] = []() -> std::unique_ptr<MQDS::Calculation> { return std::make_unique<T>();};
            return true;
        }
        return false;
    }

private:
    static std::map<std::string, TCreateCalculationClass>& calculation_classes_(){
        static std::map<std::string, TCreateCalculationClass> c_classes;
        return c_classes;
    };
};


#endif //MQDS_CALCULATION_FACTORY_H
