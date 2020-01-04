#include "Sorceress.h"
#include "BFS.h"
#include "Empty.h"
#include <iostream>


Sorceress::Sorceress(Position _position, const vector<vector<char>>& symbols) : Entity(_position), moved(false)
{
	findPath(symbols, _position, findPortal(symbols));
}

char Sorceress::getSymbol() const
{
	return 'S';
}

bool Sorceress::canMove() const
{
	return true;
}

bool Sorceress::hasMoved() const
{
	return moved;
}

void Sorceress::setMoved(bool _moved)
{
	moved = _moved;
}

void Sorceress::move(Labyrinth& labyrinth)
{
	if (path.empty())
		return;
	
	//Position oldPosition(getPosition());

	Position newPosition(path.top());

	path.pop();

	Entity* thisEntity = reinterpret_cast<Entity*>(this);
	
	labyrinth.moveEntity(thisEntity, newPosition);
	

	//labyrinth.swapEntities(oldPosition, newPosition);

	
	

	/*
	
	Entity* thisEntity = reinterpret_cast<Entity*>(this);

	Entity* destEntity = labyrinth.getEntityAt(newPosition);

	char destSymbol = destEntity->getSymbol();

	if (destSymbol == 'O')
		insidePortal = true;
	if (destSymbol == '*')
		dead = true;
	
	labyrinth.moveEntity(thisEntity, newPosition);

	++nextStep;

	*/
	
}



void Sorceress::findPath(const vector<vector<char>>& symbols, Position start, Position finish)
{

	BFS bfs;
	Pathfinding* pathfinding = &bfs;
	

	

	path = pathfinding->findPath(symbols, start, finish);
}


Position Sorceress::findPortal(const vector<vector<char>>& symbols) const
{
	for (int i = 0; i < symbols.size(); ++i)
		for (int j = 0; j < symbols[i].size(); j++)
			if (symbols[i][j] == 'O')
				return { i, j };

	return getPosition();
}
