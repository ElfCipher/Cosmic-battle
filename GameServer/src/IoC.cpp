#include "IoC.h"

namespace Server
{

thread_local IoC::PScope IoC::currentScope = nullptr;
IoC::PScope IoC::rootScope = std::make_shared<IoC::Scope>();

} // namespace Server
