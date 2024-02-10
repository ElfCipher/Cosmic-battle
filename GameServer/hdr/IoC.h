#pragma once

#include <functional>
#include <memory>
#include <map>
#include "ICommand.h"
#include "ArgumentException.h"

namespace Server
{

template<class T, class ...Args>
class InitCmd;

class IoC
{
public:
    template<class T, class ...Args>
    using Generator = std::function<std::shared_ptr<T>(Args...)>;

    template<class T, class ...Args>
    static std::shared_ptr<T> Resolve(const std::string& dependency, Args... args)
    {
        auto factory = factoryMap<T>.find(dependency);
        if(factory == factoryMap<T>.end())
            throw ArgumentException(dependency);

        return std::any_cast<Generator<T, Args...>>(factory->second)(args...);
    }

    using Map = std::map<std::string, std::any>;

    template<class T>
    static Map factoryMap;
};

template<class T, class ...Args>
class Register : public ICommand
{
public:
    Register(std::string str, IoC::Generator<T, Args...> func) : str(str), func(func) {}
    virtual ~Register() {}
    virtual void Execute() override {
        IoC::factoryMap<T>[str] = func;
    }
protected:
    std::string str;
    IoC::Generator<T, Args...> func;
};

template<class T, class ...Args>
class InitCmd : public ICommand
{
public:
    InitCmd() {}
    virtual ~InitCmd() {}
    virtual void Execute() override {
        if(isInitialized)
            return;

        static IoC::Generator<ICommand, std::string, IoC::Generator<T, Args...>> gen = [](std::string str, IoC::Generator<T, Args...> func) {
            return std::make_shared<Register<T, Args...>>(str, func);
        };
        IoC::factoryMap<ICommand>["Register"] = gen;


        // static IoC::Generator<std::map<std::string, std::any>> emptyScope = [](){
        //     return std::make_shared<std::map<std::string, std::any>>();
        // };
        // IoC::factoryMap<T>["IoC.Scope.Create.Empty"] = emptyScope;

        isInitialized = true;
    }
protected:
    static bool isInitialized;
};

template<class T, class ...Args>
bool InitCmd<T, Args...>::isInitialized = false;

template<class T>
IoC::Map IoC::factoryMap = IoC::Map();

} // namespace Server
