#pragma once
#include "Entity.h"
#include <vector>
#include <ostream>

using namespace std;

class Labyrinth
{
private:


	vector<vector<Entity*>> entities;
	
	
	int monsterCount;


	void fillEntities(vector<vector<char>>&);

public:
	
	Labyrinth(vector<vector<char>>&, int);

	vector<Entity*> operator[](int);

	int width() const;
	int height() const;

	Entity* getEntityAt(Position)const;
	

	
	
	friend ostream& operator<<(ostream&, const Labyrinth&);
	
};







