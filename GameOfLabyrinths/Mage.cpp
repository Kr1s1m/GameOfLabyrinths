#include "Mage.h"
#include "DFS.h"

Mage::Mage(Position _position) : Entity(_position)
{

}

char Mage::getSymbol() const
{
	return 'M';
}

bool Mage::canMove() const
{
	return true;
}

void Mage::move(Labyrinth& labyrinth)
{
	if (path.empty())
		return;

	Position oldPosition(getPosition());

	Position newPosition(path.top());

	labyrinth.swapEntities(oldPosition, newPosition);

	path.pop();


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


void Mage::findPath(vector<vector<char>>& symbols, Position start, Position finish)
{

	DFS dfs;
	Pathfinding* pathfinding = &dfs;




	path = pathfinding->findPath(symbols, start, finish);
}

void Mage::setPath(stack<Position>& _path)
{
	path = _path;

}