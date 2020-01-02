#include "Labyrinth.h"
#include "Empty.h"
#include "Wall.h"
#include <iostream>
#include <queue>

void Labyrinth::fillEntities(vector<vector<char>>& symbols)
{

	

	for(int i = 0; i < symbols.size(); ++i)
	{
		for(int j = 0; j < symbols[i].size(); ++j)
		{
			if (symbols[i][j] == '.')
			{
				entities[i][j] = new Empty({ i, j });
			}
			else
				entities[i][j] = new Wall({ i, j });
		}
	}

}

Labyrinth::Labyrinth(vector<vector<char>>& symbols, int _monsterCount) : monsterCount(_monsterCount)
{
	fillEntities(symbols);
}

vector<Entity*> Labyrinth::operator[](int index)
{
	if(index > entities.size() || index < 0)
	{
		cout << "array index out of bound";

		exit(0);
	}

	return entities[index];

}

int Labyrinth::width() const
{
	return entities.begin()->size();
}

int Labyrinth::height() const
{
	return entities.size();
}

Entity* Labyrinth::getEntityAt(Position position) const
{
	return entities[position.getX()][position.getY()];
}





ostream& operator<<(ostream& os, const Labyrinth& labyrinth)
{
	for(auto& entityArray : labyrinth.entities)
	{
		for(auto& entity : entityArray)
		{
			os << entity->getSymbol() << ' ';
		}

		os << '\n';
	}

	return os;
}

