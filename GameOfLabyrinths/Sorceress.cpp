#include "Sorceress.h"
#include "BFS.h"
#include "Empty.h"


Sorceress::Sorceress(Position _position) : Entity(_position), insidePortal(false), dead(false)
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
	
	Entity* thisEntity = reinterpret_cast<Entity*>(this);

	Entity* destEntity = labyrinth.getEntityAt(newPosition);

	char destSymbol = destEntity->getSymbol();

	if (destSymbol == 'O')
		insidePortal = true;
	if (destSymbol == '*')
		dead = true;
	
	labyrinth.moveEntity(thisEntity, newPosition);

	++nextStep;


	
}

bool Sorceress::isInsidePortal() const
{
	return insidePortal;
}

bool Sorceress::isDead() const
{
	return dead;
}

void Sorceress::findPath(vector<vector<char>>& symbols, Position start, Position finish)
{
	Pathfinding* pathfinding;
	BFS bfs;

	pathfinding = &bfs;

	path = pathfinding->findPath(symbols, start, finish);
}
