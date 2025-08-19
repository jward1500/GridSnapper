#include "level.hpp"

GridSpace Level::GetGridSpace(Pos pos) {

	// if not in bounds, behave like this is an obstacle
	if (!inBounds(pos)) {
		return GridSpace::OBSTACLE;
	}
	else {
		return level_grid[pos.y][pos.x];
	}
}

void Level::ClearSpace(Pos pos) {
	if (inBounds(pos)) {
		// store the deleted space
		deleted_spaces.push_back({ pos, level_grid[pos.y][pos.x] });

		// delete the space
		level_grid[pos.y][pos.x] = GridSpace::EMPTY;
	}
}

void Level::RestoreSpaces() {
	for (int i = 0; i < deleted_spaces.size(); ++i) {
		DeletedSpace d = deleted_spaces[i];
		level_grid[d.pos.y][d.pos.x] = d.grid_space;
	}
}


bool Level::inBounds(Pos pos) {
	if (pos.y > level_grid.size() - 1 ||
		pos.x > level_grid[0].size() - 1 ||
		pos.y < 0 ||
		pos.x < 0)
	{
		return false;
	}
	else {
		return true;
	}
}