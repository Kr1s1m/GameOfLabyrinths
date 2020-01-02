#include "Playerwall.h"

Playerwall::Playerwall(Position _position) : Entity(_position)
{
	
}

char Playerwall::getSymbol() const
{
	return '$';
}

bool Playerwall::canMove() const
{
	return false;
}




