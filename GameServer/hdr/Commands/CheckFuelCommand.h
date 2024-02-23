#pragma once

#include "ICommand.h"
#include "Objects/IFuelable.h"
#include <Exception.h>
#include <sstream>

namespace Server
{

class CheckFuelCommand : public ICommand
{
public:
    CheckFuelCommand(PIFuelable fuelable);
    virtual ~CheckFuelCommand() { }
    virtual void Execute() override;

    class CheckFuelException : public Exception
    {
    public:
        CheckFuelException(PIFuelable fuelable) {
            std::stringstream ss;
            ss << "Object " << typeid(*fuelable).name() << " has only " << fuelable->getFuel() << " fuel";
            msg = ss.str();
        }
        virtual ~CheckFuelException() { }
    };

protected:
    PIFuelable fuelable;
};

} // namespace Server
