#pragma once

#include "UObject.h"
#include "ICommand.h"
#include "Objects/IMovable.h"
#include "Exception.h"

namespace Server
{

class SetPositionCommand : public ICommand
{
public:
    SetPositionCommand(PUObject obj, Vector newPosition) :
        obj(obj), newPosition(newPosition) {}
    virtual ~SetPositionCommand() {}
    virtual void Execute() override
    {
        auto property = obj->find("Position");
        if(property == obj->end())
            throw Exception("No such property - Position");

        property->second = newPosition;
    }

protected:
    PUObject obj;
    Vector newPosition;
};

} // namespace Server
