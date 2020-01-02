#include "Empty.h"

Empty::Empty(Position _position) : Entity(_position)
{
	
}

char Empty::getSymbol() const
{
	return '.';
}

bool Empty::canMove() const
{
	return false;
}