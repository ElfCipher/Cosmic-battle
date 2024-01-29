#include "Move.h"

namespace Server
{

Move::Move(std::shared_ptr<IMovable> m) :
    m(m)
{
}

void Move::Execute()
{
    m->setPosition(m->getPosition() + m->getVelocity());
}

} // namespace Server
