#include "Mage.h"
#include "DFS.h"

Mage::Mage(Position _position, const vector<vector<char>>& symbols) : Entity(_position), moved(false)
{
	findPath(symbols, _position, findPortal(symbols));
}

char Mage::getSymbol() const
{
	return 'M';
}

bool Mage::canMove() const
{
	return true;
}

bool Mage::hasMoved() const
{
	return moved;
}

void Mage::setMoved(bool _moved)
{
	moved = _moved;
}

void Mage::move(Labyrinth& labyrinth)
{
	if (path.empty())
		return;

	Position newPosition(path.top());

	path.pop();

	Entity* thisEntity = reinterpret_cast<Entity*>(this);

	labyrinth.moveEntity(thisEntity, newPosition);


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


void Mage::findPath(const vector<vector<char>>& symbols, Position start, Position finish)
{

	DFS dfs;
	Pathfinding* pathfinding = &dfs;

	path = pathfinding->findPath(symbols, start, finish);
}

Position Mage::findPortal(const vector<vector<char>>& symbols) const
{
	for (int i = 0; i < symbols.size(); ++i)
		for (int j = 0; j < symbols[i].size(); j++)
			if (symbols[i][j] == 'O')
				return { i, j };

	return getPosition();
}

