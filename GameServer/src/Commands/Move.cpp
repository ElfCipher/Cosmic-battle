#include "Move.h"

namespace Server
{

Move::Move(PIMovable m) :
    m(m)
{
}

void Move::Execute()
{
    m->setPosition(m->getPosition() + m->getVelocity());
}

} // namespace Server
