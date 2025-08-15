#include "game.hpp"
#include "levelData.hpp"

#include <iostream>

using std::vector;
using std::string;

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



void Game::pullTimeRecords() {

	// open the save file (save file should be here)
	std::ifstream save_file_input("save_file.txt");

	for (int i = 0; i < 5; ++i) {
		std::string record_holder;
		uint64_t time;
		save_file_input >> record_holder >> time;
		top_times.push_back({record_holder, time});
	}

	save_file_input >> snap_lines_high_score_index;

	// has the player beat snap legit?
	save_file_input >> has_beat_snap;
	
	// if the player has edited the time but not "beat snap legit"
	save_file_input >> has_cheated_and_beat_snap;
	if (top_times[0].record_holder != "SNAP" && !has_beat_snap) {
		has_cheated_and_beat_snap = true;
	}
	else {
		has_cheated_and_beat_snap = false;
	}

	save_file_input.close();

	// DEBUG
	for (auto& record : top_times) {
		std::cout << record.record_holder << " " << record.time << std::endl;
	}
	std::cout << snap_lines_high_score_index << std::endl;
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

void Game::InsertNewRecord(string const& player_name) {

	// if the total time is better than snap, player has legitimately beat snap
	if (current_game_stats.total_time < 35000) {
		has_beat_snap = true;
		has_cheated_and_beat_snap = false;
	}

	for (auto itr = top_times.begin(); itr < top_times.end(); ++itr) {
		if (current_game_stats.total_time < itr->time) {
			top_times.insert(itr, { player_name, current_game_stats.total_time });
			break;
		}
	}
	top_times.resize(5);
}

void Game::SaveGame() {
	// overwrite save data with top times data structure
	std::ofstream save_file_output("save_file.txt", std::ios::trunc);
	for (auto& record : top_times) {
		save_file_output << record.record_holder << " " << record.time << std::endl;
	}
	save_file_output << snap_lines_high_score_index << std::endl;
	save_file_output << has_beat_snap << std::endl;
	save_file_output << has_cheated_and_beat_snap << std::endl;
	save_file_output.close();
}

bool Game::WasRecordSet() {
	for (auto& record : top_times) {
		if (current_game_stats.total_time < record.time) { return true; };
	}
	return false;
}

vector<Record> Game::GetTopTimes() {
	return top_times;
}

int Game::GetSnapLinesHighScoreIndex() {
	return snap_lines_high_score_index;
}

void Game::IncrementSnapLinesHighScoreIndex() {
	++snap_lines_high_score_index;
	SaveGame();
}

bool Game::HasCheated() {
	return has_cheated_and_beat_snap;
}

bool Game::HasBeatSnap() {
	return has_beat_snap;
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