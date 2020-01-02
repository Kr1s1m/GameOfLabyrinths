#include "Sorceress.h"
#include "BFS.h"
#include "Empty.h"


Sorceress::Sorceress(Position _position) : Entity(_position), dead(false), insidePortal(false)
{
	
}

char Sorceress::getSymbol() const
{
	return 'S';
}

bool Sorceress::canMove() const
{
	return true;
}

void Sorceress::move(Labyrinth& labyrinth)
{
	if (nextStep == path.end()) 
		return;
		

	Position oldPosition(getPosition());

	Position newPosition(*nextStep);

	
	Entity* current = labyrinth.getEntityAt(oldPosition);
	Entity* destination = labyrinth.getEntityAt(newPosition);

	if (destination->getSymbol() == 'O')
	{
		insidePortal = true;
		delete current;
		current = new Empty(oldPosition);
		
	}
	else if(destination->getSymbol() == '*')
	{
		dead = true;
		delete current;
		current = new Empty(oldPosition);
	}
	else if(destination->getSymbol() == '.')
	{
		delete destination;
		updatePosition(newPosition);
		destination = this;
		delete current;
		current = new Empty(oldPosition);
	}
	
}

bool Sorceress::isInsidePortal() const
{
	return insidePortal;
}

bool Sorceress::isDead() const
{
	return dead;
}

void Sorceress::findPath(const Labyrinth& labyrinth)
{
	Pathfinding* pathfinding;
	BFS bfs;

	pathfinding = &bfs;

	path = pathfinding->findPath(labyrinth);
}
