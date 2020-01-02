#include "Position.h"

Position::Position(int _x, int _y) : x(_x), y(_y)
{
	
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

bool Position::operator==(const Position& other) const
{
	return (x == other.getX() && y == other.getY());
}

Position Position::operator+(const Position& other) const
{
	return { x + other.getX(), y + other.getY() };
}
