#pragma once

#include "ICommand.h"
#include "IoC.h"

namespace Server
{

class Register : public ICommand // Команда для регистрации лямбды, создающей необходимый тип
{
public:
    Register(std::string str, std::any func) : str(str), func(func) {}
    virtual ~Register() {}
    virtual void Execute() override {
        IoC::Resolve<IoC::Scope>("IoC.Scope.Current")->emplace(str, func);
    }
protected:
    std::string str;
    std::any func;
};

} // namespace Server
