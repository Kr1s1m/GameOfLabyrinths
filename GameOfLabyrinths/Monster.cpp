#include "Monster.h"

Monster::Monster(Position _position) : Entity(_position)
{
	
}

char Monster::getSymbol() const
{
	return '*';
}

bool Monster::canMove() const
{
	return true;
}

void Monster::move(Labyrinth& labyrinth)
{
	
}
