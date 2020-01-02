#pragma once
class Position
{
private:

	int x;
	int y;

public:
	

	Position(int = -1, int = -1);

	int getX() const;
	int getY() const;

	bool operator==(const Position&) const;

	Position operator+(const Position&) const;
	
};

