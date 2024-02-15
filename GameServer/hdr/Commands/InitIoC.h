#pragma once

#include "Register.h"

namespace Server
{

class InitIoC : public ICommand // Команда для инициализации начанльный зависимостей (команды Register, создание скоупа и т.д.).
{                               // Должна исполниться один раз для нового типа
public:
    InitIoC() {}
    virtual ~InitIoC() {}
    virtual void Execute() override;

protected:
    static bool isInitialized;
};

} // namespace Server
