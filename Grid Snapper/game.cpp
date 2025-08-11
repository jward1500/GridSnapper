#include "game.hpp"

#include <iostream>
using namespace std;

using std::vector;

Game::Game() {
	// always start player in bottom-left corner
	pos = { 0, 5 };
	current_level = 0;

	pullTimeRecords();
	setLevelData();

	// set all current level times to 0
	current_game_stats.level_times.resize(10);
	for (int i = 0; i < current_game_stats.level_times.size(); ++i) {
		current_game_stats.level_times[i] = 0;
	}
}

// later, this function will attempt to pull old records from the persistent data
// for now, it just initializes them to 0 ms
void Game::pullTimeRecords() {
	for (int i = 0; i < top_times.size(); ++i) {
		top_times.push_back(0);
	}
}

MoveResult Game::Move(MoveDirection dir) {
	Level level = levels[current_level];

	Pos next_pos = pos;
	switch (dir) {
	case MoveDirection::LEFT:
		next_pos = { pos.x - 1, pos.y };
		break;
	case MoveDirection::RIGHT:
		next_pos = { pos.x + 1, pos.y };
		break;
	case MoveDirection::UP:
		next_pos = { pos.x, pos.y - 1 };
		break;
	case MoveDirection::DOWN:
		next_pos = { pos.x, pos.y + 1 };
	}

	GridSpace future_space = level.GetGridSpace(next_pos);
	if (future_space == GridSpace::OBSTACLE) {
		return MoveResult::DIE;
	}
	else if (future_space == GridSpace::GOAL) {
		return MoveResult::WIN;
	}
	else {
		pos = next_pos;
		return MoveResult::SUCCESS;
	}
}

GridSpace Game::GetGridSpace(Pos pos) {
	Level level = levels[current_level];
	return level.GetGridSpace(pos);
}

void Game::ResetCurrentLevel() {
	pos = { 0 , 5 };
}

void Game::IncrementDeathCounter() {
	++current_game_stats.deaths;
}

int Game::GetDeathCount() {
	return current_game_stats.deaths;
}

Pos Game::GetPlayerPos() {
	return pos;
}

int Game::GetCurrentLevel() {
	return current_level + 1;
}

bool Game::IncrementCurrentLevel() {
	if (current_level == 9) { return false; }
	++current_level;
	return true;
}

void Game::SetCurrentLevelTime(uint64_t t) {
	current_game_stats.level_times[current_level] = t;
}

// this hard code the level data for now, it will manually set the matrices in the level objects
void Game::setLevelData() {

	std::vector<std::vector<GridSpace>> level_1 = {
	{
			// 1
			GridSpace::GOAL,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		},
		{
			// 2
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 3
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		},
		{
			// 4
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE
		},
		{
			// 5
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		}
	};

	std::vector<std::vector<GridSpace>> level_2 = {
	{
			// 1
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		},
		{
			// 3
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		},
		{
			// 4
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::GOAL
		},
		{
			// 5
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		}
	};

	levels.push_back(Level(level_1));
	levels.push_back(Level(level_2));
}