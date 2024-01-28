#include "Move.h"

namespace Server
{

Move::Move(Vector startPosition, Vector velocity) :
    IMovable(velocity)
{
    position = startPosition;
}

void Move::Execute()
{
    setPosition(position + velocity);
}

} // namespace Server
