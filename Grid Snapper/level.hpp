#pragma once

#include <vector>

struct Pos {
	int x, y;
};

enum class GridSpace {
	EMPTY,
	OBSTACLE,
	GOAL
};

class Level {

public:
	// constructing a level must provide the entire level data
	Level(std::vector<std::vector<GridSpace>> const& level_data) : level_grid(level_data) {};

	// will return the type of space at the given coordinates, if out of bounds, will return OBSTACLE since this is expected
	GridSpace GetGridSpace(Pos pos);

private:
	std::vector<std::vector<GridSpace>> level_grid;
};