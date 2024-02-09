#pragma once

#include "ICommand.h"
#include "Objects/Fuelable.h"
#include <Exception.h>
#include <sstream>

namespace Server
{

class CheckFuelCommand : public ICommand
{
public:
    CheckFuelCommand(PFuelable fuelable);
    virtual ~CheckFuelCommand() { }
    virtual void Execute() override;

    class CheckFuelException : public Exception
    {
    public:
        CheckFuelException(PFuelable fuelable) {
            std::stringstream ss;
            ss << "Object " << typeid(*fuelable).name() << " has only " << fuelable->getFuel() << " fuel";
            msg = ss.str();
        }
        virtual ~CheckFuelException() { }
    };

protected:
    PFuelable fuelable;
};

} // namespace Server
