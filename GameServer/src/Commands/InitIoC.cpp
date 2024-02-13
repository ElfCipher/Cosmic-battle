#include "InitIoC.h"
#include "SetCurrentScope.h"
#include "ClearCurrentScope.h"

namespace Server
{

bool InitIoC::isInitialized = false;

void InitIoC::Execute()
{
    if(isInitialized)
        return;

    static IoC::Generator<ICommand, std::string, std::any> gen = [](std::string str, std::any func) {
        if(std::string(func.type().name()).find("function") == std::string::npos)
            throw ArgumentException("lambda or other");

        return std::make_shared<Register>(str, func);
    };
    IoC::rootScope->emplace("IoC.Register", gen);


    static IoC::Generator<IoC::Scope> createEmptyScope = [](){
        return std::make_shared<IoC::Scope>();
    };
    IoC::rootScope->emplace("IoC.Scope.New.Empty", createEmptyScope);


    static IoC::Generator<IoC::Scope, IoC::PScope> createScope = [](IoC::PScope parent) {
        auto scope = IoC::Resolve<IoC::Scope>("IoC.Scope.New.Empty");

        if(!parent)
            parent = IoC::rootScope;

        IoC::Generator<IoC::Scope> getParent = [parent](){
                return parent;
        };
        scope->emplace("IoC.Scope.Parent", getParent);

        return scope;
    };
    IoC::rootScope->emplace("IoC.Scope.New", createScope);


    static IoC::Generator<IoC::Scope> getParentFromRoot = []() -> IoC::PScope {
        throw Exception("The root scope has no a parent scope.");
    };
    IoC::rootScope->emplace("IoC.Scope.Parent", getParentFromRoot);


    static IoC::Generator<IoC::Scope> getCurrentScope = []() {
        return IoC::currentScope ? IoC::currentScope : IoC::rootScope;
    };
    IoC::rootScope->emplace("IoC.Scope.Current", getCurrentScope);


    static IoC::Generator<ICommand, IoC::PScope> setCurrentScope = [](IoC::PScope scope) {
        return std::make_shared<SetCurrentScope>(scope);
    };
    IoC::rootScope->emplace("IoC.Scope.Current.Set", setCurrentScope);


    static IoC::Generator<ICommand> clearCurrentScope = []() {
        return std::make_shared<ClearCurrentScope>();
    };
    IoC::rootScope->emplace("IoC.Scope.Current.Set", setCurrentScope);

    isInitialized = true;
}

} // namespace Server
