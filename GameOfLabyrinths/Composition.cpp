#include "Composition.h"

Composition::Composition(Position _position, Entity* _first, Entity* _second ) : Entity(_position), first(_first), second(_second)
{
	
}

Entity* Composition::getFirst() const
{
	return first;
}

Entity* Composition::getSecond() const
{
	return second;
}

char Composition::getSymbol() const
{
	return first->getSymbol();
}

bool Composition::canMove() const
{
	return second->canMove();
}

void Composition::move(Labyrinth& labyrinth)
{

	second->move(labyrinth);
	
}




