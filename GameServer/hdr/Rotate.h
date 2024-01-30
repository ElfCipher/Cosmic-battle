#pragma once

#include "ICommand.h"
#include "Rotable.h"
#include <memory>

namespace Server
{

class Rotate : public ICommand
{
public:
    Rotate(std::shared_ptr<IRotable> r);
    virtual ~Rotate() {}
    virtual void Execute() override;

    std::shared_ptr<IRotable> r;
};

} // namespace Server
