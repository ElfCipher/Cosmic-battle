#pragma once

#include <string>

namespace Server
{

struct CommonMessage
{
    uint64_t gameId;
    uint64_t objectId;
    uint64_t operationId;
    std::string json;
};

} // namespace Server
