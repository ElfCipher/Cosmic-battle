#pragma once

#include <string>
#include <map>

namespace Server
{

/**
 * @brief Хранит словарь из id команды и её названием зависимоти.
 * Это нужно для того, чтобы не допустить исполнения непредназначенной для Агента команды
 */
class CommandsHolder
{
private:
    CommandsHolder() {}
    std::map<uint64_t, std::string> commands; // operationId - IoC dependency 

public:
    static CommandsHolder& Locate() {
        static CommandsHolder holder;
        return holder;
    }

    void Register(uint64_t operationId, std::string dependency) {
        commands.emplace(operationId, dependency);
    }
    
    std::string GetDependency(uint64_t operationId) {
        auto dep = commands.find(operationId);
        
        if(dep == commands.end())
            return "";

        return dep->second;
    }
};

} // namespace Server
