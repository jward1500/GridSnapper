#pragma once

#include "level.hpp"
#include <vector>

// dynamic struct representing the player's game state
struct GameStats {
	int deaths = 0;
	std::vector<uint32_t> level_times;
	uint32_t total_time;
};

enum class MoveDirection {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class MoveResult {
	SUCCESS,
	DIE,
	WIN
};

class Game {
public:
	Game();
	MoveResult Move(MoveDirection dir);

	// get the grid space on the current level
	GridSpace GetGridSpace(Pos pos);

	// reset the level in the context of a death
	void ResetCurrentLevel();

	void IncrementDeathCounter();

	int GetDeathCount();

	Pos GetPlayerPos();

	int GetCurrentLevel();

	// returns false if the player is on the last level
	bool IncrementCurrentLevel();

	void SetCurrentLevelTime(uint64_t t);

	// assumes the game is finished
	GameStats GetLevelStats();

private:
	std::vector<Level> levels;
	std::vector<uint32_t> top_times;
	GameStats current_game_stats;
	Pos pos;
	int current_level;

	// helper functions
	void pullTimeRecords();
	void setLevelData();
};