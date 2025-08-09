#include "level.hpp"

GridSpace Level::GetGridSpace(Pos pos) {

	// if not in bounds, behave like this is an obstacle
	if (pos.y > level_grid.size() - 1 || 
		pos.x > level_grid[0].size() - 1 ||
		pos.y < 0 ||
		pos.x < 0)
	{
		return GridSpace::OBSTACLE;
	}
	else {
		return level_grid[pos.y][pos.x];
	}
}