#pragma once

#include <vector>

struct Pos {
	int x, y;
};

enum class GridSpace {
	EMPTY,
	OBSTACLE,
	GOAL,
	FLIP,
	INVIS,
	DARK,
	SPAM
};

struct DeletedSpace {
	Pos pos;
	GridSpace grid_space;
};

class Level {

public:
	// constructing a level must provide the entire level data
	Level(std::vector<std::vector<GridSpace>> const& level_data) : level_grid(level_data) {};

	// will return the type of space at the given coordinates, if out of bounds, will return OBSTACLE since this is expected
	GridSpace GetGridSpace(Pos pos);

	// will clear the space back to to EMPTY
	void ClearSpace(Pos pos);

	// restore all deleted spaces
	void RestoreSpaces();

private:
	std::vector<std::vector<GridSpace>> level_grid;
	std::vector<DeletedSpace> deleted_spaces;

	// determine if a position is in bounds
	bool inBounds(Pos pos);
};