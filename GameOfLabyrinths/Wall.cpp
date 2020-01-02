#include "Wall.h"

Wall::Wall(Position _position) : Entity(_position)
{
	
}

char Wall::getSymbol() const
{
	return '#';
}

bool Wall::canMove() const
{
	return false;
}

void Wall::move()
{
	
}
