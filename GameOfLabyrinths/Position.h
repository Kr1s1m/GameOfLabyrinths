#pragma once
#include <cmath>

class Position
{
private:

	int x;
	int y;

public:
	

	Position(int = -1, int = -1);
	Position(const Position&);

	int getX() const;
	int getY() const;

	bool operator==(const Position&) const;

	Position operator+(const Position&) const;
	bool outOfBounds(int, int) const;

	long distanceFromOrigin() const;

	bool operator<(const Position&) const;
};

