#pragma once

#include <string>
#include <map>
#include <any>
#include <functional>
#include "Exceptions/Exception.h"
#include <list>
#include <memory>

namespace Server
{
    
class Context
{
public:
    void Set(std::string key, std::any value) {
        store[key] = value;
    }

    std::any Get(std::string key) {
        auto it = store.find(key);
        if(it == store.end())
            return std::any();

        return it->second;
    }

protected:
    std::map<std::string, std::any> store;
};


class ICorWorker
{
public:
    virtual void Execute(Context context) = 0;
};


class CorWorker : public ICorWorker
{
public:
    using IOn = std::function<bool(Context)>;
    using IHandler = std::function<void(Context)>;
    using IEHandler = std::function<void(Context, Exception)>;

    CorWorker(IOn on, IHandler handler, IEHandler ehandler) :
        on(on), handler(handler), ehandler(ehandler)
    { }

    virtual void Execute(Context context) override
    {
        if(on(context))
        {
            try {
                handler(context);
            }
            catch(const Exception& e) {
                ehandler(context, e);
            }
            
        }
    }

protected:
    IOn on;
    IHandler handler;
    IEHandler ehandler;
};


class CorChain : public ICorWorker
{
public:
    CorChain(const std::list<std::shared_ptr<ICorWorker>>& list) :
        list(list)
    { }

    virtual void Execute(Context context) override
    {
        for(auto it : list)
            it->Execute(context);
    }

protected:
    std::list<std::shared_ptr<ICorWorker>> list;
};

} // namespace Server
