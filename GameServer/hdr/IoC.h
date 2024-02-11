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
        auto factory = factoryMap<T, Args...>.find(dependency);
        if(factory == factoryMap<T, Args...>.end())
            throw ArgumentException(dependency);

        return std::any_cast<Generator<T, Args...>>(factory->second)(args...);
    }

    using Map = std::map<std::string, std::any>;
    using PMap = std::shared_ptr<Map>;

    template<class T, class ...Args>
    static Map factoryMap;
};



template<class T, class ...Args>
class Register : public ICommand // Команда для регистрации лямбды, создающей необходимый тип
{
public:
    Register(std::string str, IoC::Generator<T, Args...> func) : str(str), func(func) {}
    virtual ~Register() {}
    virtual void Execute() override {
        IoC::factoryMap<T, Args...>[str] = func;
    }
protected:
    std::string str;
    IoC::Generator<T, Args...> func;
};



template<class T, class ...Args>
class InitCmd : public ICommand // Команда для инициализации начанльный зависимостей (команды Register, создание скоупа и т.д.).
{                               // Должна исполниться один раз для нового типа
public:
    InitCmd() {}
    virtual ~InitCmd() {}
    virtual void Execute() override {
        if(isInitialized)
            return;

        static IoC::Generator<ICommand, std::string, IoC::Generator<T, Args...>> gen = [](std::string str, IoC::Generator<T, Args...> func) {
            return std::make_shared<Register<T, Args...>>(str, func);
        };
        IoC::factoryMap<ICommand, std::string, IoC::Generator<T, Args...>>["IoC.Register"] = gen;


        static IoC::Generator<IoC::Map> createScope = [](){ // TODO: как регистрировать только один раз? куда положить?
            return std::make_shared<IoC::Map>();
        };
        IoC::factoryMap<IoC::Map>["IoC.Scope.New"] = createScope;

        isInitialized = true;
    }
protected:
    static bool isInitialized;
};

template<class T, class ...Args>
bool InitCmd<T, Args...>::isInitialized = false;

template<class T, class ...Args>
IoC::Map IoC::factoryMap = IoC::Map();

} // namespace Server
