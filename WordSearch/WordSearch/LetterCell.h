#pragma once
struct LetterCell
{
	char Letter;
	LetterCell* Pointers[8];
	enum DIRECTIONS
	{
		NORTHWEST = 0,
		NORTH = 1,
		NORTHEAST = 2,
		WEST = 3,
		EAST = 4,
		SOUTHWEST = 5,
		SOUTH = 6,
		SOUTHEAST = 7
	};
};

