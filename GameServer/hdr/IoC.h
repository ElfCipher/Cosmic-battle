#pragma once

#include <functional>
#include <memory>
#include <map>
#include "ICommand.h"
#include "ArgumentException.h"
#include <any>

namespace Server
{

class IoC
{
public:
    template<class T, class ...Args>
    using Generator = std::function<std::shared_ptr<T>(Args...)>;

    template<class T, class ...Args>
    static std::shared_ptr<T> Resolve(const std::string& dependency, Args... args)
    {
        auto scope = currentScope ? currentScope : rootScope;
        auto generator = scope->find(dependency);
        if(generator == scope->end())
            while (true)
            {
                if(scope == rootScope)  // если не нашли зависимость и скоуп был уже рутовым, то ArgumentException
                    throw ArgumentException(dependency);
                
                scope = std::any_cast<Generator<IoC::Scope>>(scope->at("IoC.Scope.Parent"))();
                generator = scope->find(dependency);
                if(generator != scope->end())
                    break;
            }
        
        return std::any_cast<Generator<T, Args...>>(generator->second)(args...);
    }

    using Scope = std::map<std::string, std::any>;
    using PScope = std::shared_ptr<Scope>;

    static thread_local PScope currentScope;
    static PScope rootScope;
};

thread_local IoC::PScope IoC::currentScope = nullptr;
IoC::PScope IoC::rootScope = std::make_shared<IoC::Scope>();

} // namespace Server
