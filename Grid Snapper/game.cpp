#include "game.hpp"
#include "levelData.hpp"

#include <iostream>

using std::vector;
using std::string;

Game::Game() {
	// always start player in bottom-left corner
	pos = { 0, 5 };
	current_level = 0;

	// open the save file (save file should be here)
	save_file.open("save_file.txt");

	pullTimeRecords();
	setLevelData();

	// set all current level times to 0
	current_game_stats.level_times.resize(10);
	for (int i = 0; i < current_game_stats.level_times.size(); ++i) {
		current_game_stats.level_times[i] = 0;
	}
}

Game::~Game() {
	save_file.close();
}

void Game::pullTimeRecords() {
	for (int i = 0; i < 5; ++i) {
		std::string record_holder;
		uint64_t time;
		save_file >> record_holder >> time;
		top_times.push_back({record_holder, time});
	}

	// DEBUG
	for (auto& record : top_times) {
		std::cout << record.record_holder << " " << record.time << std::endl;
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
	current_game_stats.total_time += t;
}

GameStats Game::GetLevelStats() {
	return current_game_stats;
}

void Game::ResetGame() {
	pos = { 0, 5 };
	current_level = 0;

	// reset all game stats
	current_game_stats.deaths = 0;
	for (int i = 0; i < current_game_stats.level_times.size(); ++i) {
		current_game_stats.level_times[i] = 0;
	}
	current_game_stats.total_time = 0;
}

void Game::SaveGame() {
	// overwrite save data with top times data structure
	for (auto& record : top_times) {
		save_file << record.record_holder << " " << record.time << std::endl;
	}
}

// this hard code the level data for now, it will manually set the matrices in the level objects
void Game::setLevelData() {
	levels.push_back(LevelData::GetLevel1());
	levels.push_back(LevelData::GetLevel2());
	levels.push_back(LevelData::GetLevel3());
	levels.push_back(LevelData::GetLevel4());
	levels.push_back(LevelData::GetLevel5());
	levels.push_back(LevelData::GetLevel6());
	levels.push_back(LevelData::GetLevel7());
	levels.push_back(LevelData::GetLevel8());
	levels.push_back(LevelData::GetLevel9());
	levels.push_back(LevelData::GetLevel10());
}