#include "Position.h"

Position::Position(int _x, int _y) : x(_x), y(_y)
{
	
}

Position::Position(const Position& other) : x(other.getX()), y(other.getY())
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

bool Position::outOfBounds(int height, int width) const
{
	return (x >= height || x < 0 || y >= width || y < 0);
}

long Position::distanceFromOrigin() const
{
	return x * x + y * y;
}

bool Position::operator<(const Position& other) const
{
	return distanceFromOrigin() < other.distanceFromOrigin();
}
