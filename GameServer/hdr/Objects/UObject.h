#pragma once

#include <map>
#include <string>
#include <any>

namespace Server
{

using UObject = std::map<std::string, std::any>;
using PUObject = std::shared_ptr<UObject>;

} // namespace Server
