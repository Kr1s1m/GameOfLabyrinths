#pragma once
#include "Entity.h"
#include <vector>
#include <ostream>

using namespace std;

class Labyrinth
{
private:


	vector< vector < Entity* > > entities;
	
	
	int monsterCount;


	Entity* createEntity(char, Position);
	void fillEntities(vector<vector<char>>&);
	

public:
	
	Labyrinth(vector<vector<char>>&, int);

	vector<Entity*> operator[](int);

	int width() const;
	int height() const;

	
	Entity*& getEntityAt(Position);
	void swapEntities(Position, Position);

	bool moveEntity(Entity*&, Position);

	Position getPortalPosition() const;
	

	
	
	friend ostream& operator<<(ostream&, const Labyrinth&);
	
};







