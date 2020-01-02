#include "Portal.h"

Portal::Portal(Position _position) : Entity(_position)
{
	
}

char Portal::getSymbol() const
{
	return 'O';
}

bool Portal::canMove() const
{
	return false;
}