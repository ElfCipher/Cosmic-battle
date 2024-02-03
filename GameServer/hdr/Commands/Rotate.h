#pragma once

#include "ICommand.h"
#include "Rotable.h"

namespace Server
{

class Rotate : public ICommand
{
public:
    Rotate(PIRotable r);
    virtual ~Rotate() {}
    virtual void Execute() override;

    PIRotable r;
};

} // namespace Server
