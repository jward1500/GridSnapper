/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>
#include <sstream>
#include "game.hpp"

using std::string;
using std::cout;
using std::endl;

/* general sdl variables used by everyone */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_FRect dst_rect;

/*---------------------------------------------*/

/* general game logic variables used by the UI */

// variables for death animation
static bool in_death_animation = false;
static Uint64 death_animation_start_time;
static Uint64 death_time_in_level;
static float deathX;
static float deathY;

// variables for winning animation
static bool in_winning_animation = false;
static Uint64 winning_animation_start_time;
static Uint64 winning_time_in_level;

// variables used for level loop UI
static bool in_game = false;
static Game game;
static Uint64 level_start_time;

// variables used for game summary animation
static bool in_game_summary_animation = false;
static Uint64 summary_animation_start_time;
static GameStats final_game_stats;

// variables used for the still game summary
static bool in_game_summary = false;
static Uint64 still_game_summary_start_time;

// variables used for the new record entry screen
static bool new_record_set = false;
static bool in_record_entry = false;
static Uint64 record_entry_start_time;
constexpr int PLAYER_NAME_MAX_LENGTH = 10;
static int current_player_letter = 0;
static string player_name = "A";

// variables used for the game menu

static bool in_game_menu = true;
enum class MenuOption {
    PLAY,
    SCORES,
    QUIT
};
static MenuOption selected_choice = MenuOption::PLAY;

// variables used for high score screen
static bool in_high_scores = false;
static bool has_beat_snap = false;
std::vector<Record> top_times;
static int snap_lines_high_score_index;
static std::vector<string> snap_lines_high_score;

/*---------------------------------------------*/

// player sprite variables
static SDL_Texture* p_texture = NULL;
static int p_texture_width = 0;
static int p_texture_height = 0;

// starting position for the player (TODO: handle this is game logic class)
static float playerX = 100.0;
static float playerY = 800.0;

// background image variables
static SDL_Texture* bg_texture = NULL;
static int bg_texture_width = 0;
static int bg_texture_height = 0;

// goal sprite variables
static SDL_Texture* g_texture = NULL;
static int g_texture_width = 0;
static int g_texture_height = 0;

// obstacle sprite variables
static SDL_Texture* o_texture = NULL;
static int o_texture_width = 0;
static int o_texture_height = 0;

// die sprite variables
static SDL_Texture* d_texture = NULL;
static int d_texture_width = 0;
static int d_texture_height = 0;

// snap textures
static SDL_Texture* s_base_texture = NULL;
static int s_base_texture_width = 0;
static int s_base_texture_height = 0;

static SDL_Texture* s_speak_texture = NULL;
static int s_speak_texture_width = 0;
static int s_speak_texture_height = 0;

static SDL_Texture* s_base_x2_texture = NULL;
static int s_base_x2_texture_width = 0;
static int s_base_x2_texture_height = 0;

static SDL_Texture* s_speak_x2_texture = NULL;
static int s_speak_x2_texture_width = 0;
static int s_speak_x2_texture_height = 0;

// croc texture
static SDL_Texture* c_texture = NULL;
static int c_texture_width = 0;
static int c_texture_height = 0;

static SDL_Texture* c_x2_texture = NULL;
static int c_x2_texture_width = 0;
static int c_x2_texture_height = 0;

// main menu box texture
static SDL_Texture* m_texture = NULL;
static int m_texture_width = 0;
static int m_texture_height = 0;

// new record trophy texture
static SDL_Texture* t_texture = NULL;
static int t_texture_width = 0;
static int t_texture_height = 0;

// dialogue box texture
static SDL_Texture* db_texture = NULL;
static int db_texture_width = 0;
static int db_texture_height = 0;

/*---------------------------------------------*/

/* constants */
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define MOVEMENT_JUMP 100;
constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 6;

/*---------------------------------------------*/


/*  Take the relative file path of the bitmap and loads it onto the given texture
    Returns a bool indicating success or failure */ 
static bool load_texture_from_BMP(const std::string& relative_file_path, SDL_Texture*& texture, int& texture_width, int& texture_height) {

    SDL_Surface* surface = NULL;
    string error_log = "";

    string basePath = SDL_GetBasePath();
    string fullPath = basePath + relative_file_path;

    // load bitmap onto surface
    surface = SDL_LoadBMP(fullPath.c_str());
    if (!surface) {
        error_log = "Couldn't load bitmap: " + fullPath;
        SDL_Log(error_log.c_str(), SDL_GetError());
        SDL_DestroySurface(surface);
        return false;
    }

    // set texture's width and height variables
    texture_width = surface->w;
    texture_height = surface->h;

    // load the surface to the texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        error_log = "Couldn't create static texture: " + fullPath;
        SDL_Log(error_log.c_str(), SDL_GetError());
        SDL_DestroySurface(surface);
        return false;
    }

    SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now. */
}

// call this function to start the level timer
void startLevel() {
    level_start_time = SDL_GetTicks(); // set the level start time to now
    game.ResetCurrentLevel();
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{

    // set the app metadata
    SDL_SetAppMetadata("Grid Snapper", "1.0", "com.game.grid-snapper");

    // initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // create the window
    if (!SDL_CreateWindowAndRenderer("Grid Snapper", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // load the player texture and the background texture
    if (!load_texture_from_BMP("resources/player.bmp", p_texture, p_texture_width, p_texture_height)) { return SDL_APP_FAILURE; };
    if (!load_texture_from_BMP("resources/game_grid.bmp", bg_texture, bg_texture_width, bg_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/goal.bmp", g_texture, g_texture_width, g_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/obstacle.bmp", o_texture, o_texture_width, o_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/die.bmp", d_texture, d_texture_width, d_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/snap.bmp", s_base_texture, s_base_texture_width, s_base_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/snap_speak.bmp", s_speak_texture, s_speak_texture_width, s_speak_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/snap_x2.bmp", s_base_x2_texture, s_base_x2_texture_width, s_base_x2_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/snap_speak_x2.bmp", s_speak_x2_texture, s_speak_x2_texture_width, s_speak_x2_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/croc.bmp", c_texture, c_texture_width, c_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/croc_x2.bmp", c_x2_texture, c_x2_texture_width, c_x2_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/main_menu_box.bmp", m_texture, m_texture_width, m_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/new_record.bmp", t_texture, t_texture_width, t_texture_height)) { return SDL_APP_FAILURE; }
    if (!load_texture_from_BMP("resources/dialogue_box.bmp", db_texture, db_texture_width, db_texture_height)) { return SDL_APP_FAILURE; }

    snap_lines_high_score = {
        "No one can beat me.",
        "Croc can try all he wants...",
        "I am the best there is.",
        "Muscle memory is my strength.",
        "Australia made me strong.",
        "You can't win.",
        "That's right, I'm talking to YOU.",
        "Yeah, YOU.",
        "I'm better than YOU.",
        "Checking again won't change anything.",
        "Checked 11 times...I'm still first.",
        "Beat me, then we'll talk."
    };
    snap_lines_high_score_index = game.GetSnapLinesHighScoreIndex();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

// set the death sprite location, mark game state as in_death_animation, set death animation timer
void activateDeathAnimation(MoveDirection dir) {

    // update the game state
    in_game = false;
    in_death_animation = true;

    // set death sprite location
    switch (dir) {
    case MoveDirection::LEFT:
        deathX = playerX - 100.0;
        deathY = playerY;
        break;
    case MoveDirection::UP:
        deathX = playerX;
        deathY = playerY - 100.0;
        break;
    case MoveDirection::RIGHT:
        deathX = playerX + 100.0;
        deathY = playerY;
        break;
    case MoveDirection::DOWN:
        deathX = playerX;
        deathY = playerY + 100.0;
        break;
    }

    // set death animation timer start to now
    death_animation_start_time = SDL_GetTicks();

    // set death time to how long user has been in the level
    death_time_in_level = SDL_GetTicks() - level_start_time;
}

void activateWinningAnimation() {
    in_game = false;
    in_winning_animation = true;

    // set winning animation timer start to now
    winning_animation_start_time = SDL_GetTicks();

    // set winning time to how long user has been in level
    winning_time_in_level = SDL_GetTicks() - level_start_time;

    // set the winning time for the level in the game data
    game.SetCurrentLevelTime(winning_time_in_level);
}

void activateNewRecordScreen() {
    in_game_summary = false;
    in_record_entry = true;
}

void activateMenuScreenFromGameSummary() {
    in_game_summary = false;
    in_game_menu = true;
}

// handle all keyboard inputs when user is in a game
void handleGameInput(SDL_Event* event) {

    MoveDirection move_direction;
    MoveResult move_result;

    switch (event->key.scancode) {
    case SDL_SCANCODE_LEFT:
        move_direction = MoveDirection::LEFT;
        move_result = game.Move(move_direction);
        break;
    case SDL_SCANCODE_UP:
        move_direction = MoveDirection::UP;
        move_result = game.Move(move_direction);
        break;
    case SDL_SCANCODE_RIGHT:
        move_direction = MoveDirection::RIGHT;
        move_result = game.Move(move_direction);
        break;
    case SDL_SCANCODE_DOWN:
        move_direction = MoveDirection::DOWN;
        move_result = game.Move(move_direction);
        break;
    default:
        move_result = MoveResult::SUCCESS;
    }

    if (move_result == MoveResult::DIE) {
        activateDeathAnimation(move_direction);
    }
    else if (move_result == MoveResult::WIN) {
        activateWinningAnimation();
    }
}

void handleGameSummaryInput(SDL_Event* event) {
    if(event->key.scancode == SDL_SCANCODE_RETURN) { 
        if (new_record_set) { activateNewRecordScreen(); }
        else { activateMenuScreenFromGameSummary(); }
    }
}

void incrementMenuOption() {
    if (selected_choice == MenuOption::SCORES) { selected_choice = MenuOption::PLAY; }
    else if (selected_choice == MenuOption::QUIT) { selected_choice = MenuOption::SCORES; }
}

void decrementMenuOption() {
    if (selected_choice == MenuOption::PLAY) { selected_choice = MenuOption::SCORES; }
    else if (selected_choice == MenuOption::SCORES) { selected_choice = MenuOption::QUIT; }
}

void activateGame() {
    game.ResetGame();
    level_start_time = SDL_GetTicks();
    in_game_menu = false;
    in_game = true;
}

void activateHighScores() {
    in_game_menu = false;
    in_high_scores = true;
    game.IncrementSnapLinesHighScoreIndex();
    snap_lines_high_score_index = game.GetSnapLinesHighScoreIndex();
    top_times = game.GetTopTimes();
}

void handleGameMenuInput(SDL_Event* event) {
    if (event->key.scancode == SDL_SCANCODE_UP) { incrementMenuOption(); }
    else if (event->key.scancode == SDL_SCANCODE_DOWN) { decrementMenuOption(); }
    else if (event->key.scancode == SDL_SCANCODE_RETURN) { 
        switch (selected_choice) {
        case MenuOption::PLAY:
            activateGame();
            break;
        case MenuOption::SCORES:
            activateHighScores();
            break;
        }
    }
}

void incrementCurrentPlayerLetter() {
    if (player_name[current_player_letter] + 1 > 'Z') {
        player_name[current_player_letter] = 'A';
    }
    else {
        ++player_name[current_player_letter];
    }
}

void decrementCurrentPlayerLetter() {
    if (player_name[current_player_letter] - 1 < 'A') {
        player_name[current_player_letter] = 'Z';
    }
    else {
        --player_name[current_player_letter];
    }
}

void nextPlayerNameLetter() {
    ++current_player_letter;
    if (current_player_letter < PLAYER_NAME_MAX_LENGTH) {
        player_name.push_back('A');
    }
}

void handleRecordEntryInput(SDL_Event* event) {

    if (event->key.scancode == SDL_SCANCODE_RETURN || current_player_letter >= PLAYER_NAME_MAX_LENGTH) {
        
        // handle name submission and record saving
        game.InsertNewRecord(player_name);
        game.SaveGame();
        in_record_entry = false;
        in_game_menu = true;
        return;
    }
    
    if (event->key.scancode == SDL_SCANCODE_UP) {
        incrementCurrentPlayerLetter();
    }
    else if (event->key.scancode == SDL_SCANCODE_DOWN) {
        decrementCurrentPlayerLetter();
    }
    else if (event->key.scancode == SDL_SCANCODE_RIGHT) {
        nextPlayerNameLetter();
    }
}

void activateMenuScreenFromHighScores() {
    in_high_scores = false;
    in_game_menu = true;
}

void handleHighScoresInput(SDL_Event* event) {
    if (event->key.scancode == SDL_SCANCODE_RETURN ||
        event->key.scancode == SDL_SCANCODE_ESCAPE) {
        activateMenuScreenFromGameSummary();
    }
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (in_game) { handleGameInput(event); }
        else if (in_game_summary) { handleGameSummaryInput(event); }
        else if (in_game_menu) { handleGameMenuInput(event); }
        else if (in_record_entry) { handleRecordEntryInput(event); }
        else if (in_high_scores) { handleHighScoresInput(event); }
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

// general purpose function to convert a time in miliseconds to a string in seconds
string formatMillisecondsString(Uint64 t) {

    std::stringstream ss;
    int seconds = t / 1000;
    t -= seconds * 1000;
    int tenths = t / 100;
    t -= tenths * 100;
    int hundredths = t / 10;

    // format the time string with these calculated values
    string seconds_padding = seconds < 10 ? "0" : "";
    ss << seconds_padding << seconds << ":" << tenths << hundredths;
    return ss.str();
}


// general purpose function to draw any rectangle sprite on the screen
void drawSprite(float x_pos, float y_pos, SDL_Texture*& texture, int& texture_width, int& texture_height) {
    dst_rect.x = x_pos;
    dst_rect.y = y_pos;
    dst_rect.w = (float)texture_width;
    dst_rect.h = (float)texture_height;
    SDL_RenderTexture(renderer, texture, NULL, &dst_rect);
}

void drawBackgroundSprite() {
    drawSprite(0.0, 0.0, bg_texture, bg_texture_width, bg_texture_height);
}

// update the player sprite postion based on the game data
void setPlayerSpritePosition() {
    Pos player_pos = game.GetPlayerPos();
    playerX = (float)player_pos.x * 100 + 100;
    playerY = (float)player_pos.y * 100 + 300;
}

void drawPlayerSprite() {
    setPlayerSpritePosition();
    drawSprite(playerX, playerY, p_texture, p_texture_width, p_texture_height);
}

void drawObstacleSprite(Pos pos) {
    float obstacleX = pos.x * 100 + 100;
    float obstacleY = pos.y * 100 + 300;
    drawSprite(obstacleX, obstacleY, o_texture, o_texture_width, o_texture_height);
}

void drawGoalSprite(Pos pos) {
    float goalX = pos.x * 100 + 100;
    float goalY = pos.y * 100 + 300;
    drawSprite(goalX, goalY, g_texture, g_texture_width, g_texture_height);
}

// death sprite location should be set already
void drawDeathSprite() {
    drawSprite(deathX, deathY, d_texture, d_texture_width, d_texture_height);
}

// use game data to determine where the obstacle and the goal sprites should be drawn
void drawObstaclesAndGoals() {
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            Pos current_pos = { i, j };
            GridSpace current_space = game.GetGridSpace(current_pos);

            // we want everything to be green in winning animation
            if (in_winning_animation) {
                if (current_space == GridSpace::OBSTACLE || current_space == GridSpace::GOAL) { drawGoalSprite(current_pos); }
            }
            // otherwise use normal sprites
            else {
                if (current_space == GridSpace::OBSTACLE) { drawObstacleSprite(current_pos); }
                else if (current_space == GridSpace::GOAL) { drawGoalSprite(current_pos); }
            }
        }
    }
}

// general purpose function used to draw debug text on the screen
void drawText(float x_pos, float y_pos, float scale, float original_scale, string text) {
    SDL_SetRenderScale(renderer, scale, scale); // set the scale to appropriate value

    // scale the x and y position according to the given scale
    float new_x = x_pos / scale;
    float new_y = y_pos / scale;

    SDL_RenderDebugText(renderer, new_x, new_y, text.c_str());

    SDL_SetRenderScale(renderer, original_scale, original_scale); // set the scale back to the original value
}

void drawDeathCounter() {
    std::stringstream ss;
    ss << "Deaths: " << game.GetDeathCount();
    drawText(100.0, 100.0, 2.0, 1.0, ss.str());
}

void drawTimer() {

    // calculate seconds, tenths, and hundredths from total ms elapsed
    Uint64 time_elapsed_ms = SDL_GetTicks() - level_start_time;
    string time_string;

    // if the player is in death animation, we want to display the time of death in red instead
    if (in_death_animation) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // set color to red
        time_elapsed_ms = death_time_in_level;
    }

    // if the player is in winning animation, we want to display the time of winning in green instead
    if (in_winning_animation) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // set color to green
        time_elapsed_ms = winning_time_in_level;
    }

    // freeze and turn red after 1 minute
    if (time_elapsed_ms >= 59999) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // set color to red
        time_string = "59:99";
    }
    else {
        time_string = formatMillisecondsString(time_elapsed_ms);
    }

    // draw the clock text
    drawText(505.0, 100.0, 5.0, 1.0, time_string);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color back to white
}

void drawLevelCounter() {
    std::stringstream ss;
    ss << game.GetCurrentLevel() << "/10";
    drawText(1000.0, 100.0, 2.0, 1.0, ss.str());
}

void drawUI() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white
    drawDeathCounter();
    drawTimer();
    drawLevelCounter();
}

/* calling this will effectively play the death animation for 2.0 seconds, and then will automatically 
   switch it out of the death animation and back to the game */ 

void executeDeathAnimation() {

    Uint32 current_animation_time = SDL_GetTicks() - death_animation_start_time;
    
    // check to see if death animation timer is up
    if (current_animation_time > 2000) {
        in_death_animation = false;
        in_game = true;
        game.IncrementDeathCounter();
        startLevel();
        return;
    }

    /* Animation sequence */

    // freeze for 0.5 seconds, no death sprite
    if (current_animation_time < 500) {
        return;
    }
    // display for 0.5 seconds 
    else if (current_animation_time < 1000) {
        drawDeathSprite();
        return;
    }
    // hide for 0.5 seconds
    else if (current_animation_time < 1500) {
        return;
    }
    else if (current_animation_time < 2000) {
        drawDeathSprite();
        return;
    }
}

void executeWinningAnimation() {

    Uint32 current_animation_time = SDL_GetTicks() - winning_animation_start_time;

    // check to see if winning animation timer is up
    if (current_animation_time > 2000) {
        in_winning_animation = false;
        
        // update the game data fow the game summary
        if (!game.IncrementCurrentLevel()) {
            final_game_stats = game.GetLevelStats();
            new_record_set = game.WasRecordSet();
            summary_animation_start_time = SDL_GetTicks();
            in_game_summary_animation = true;
        }
        else {
            in_game = true;
            startLevel();
        }

        return;
    }
}

void drawSummaryTitleText() {
    drawText(362.5, 100.0, 5.0, 1.0, "GAME RESULTS");
}

void drawDeathResultText() {
    std::stringstream ss;
    ss << "Deaths: " << final_game_stats.deaths;
    drawText(300.0, 200.0, 2.0, 1.0, ss.str());
}

// takes a parameter to control how many level times are displayed out of the ten
void drawLevelTimes(int num_levels) {
    for (int i = 0; i < num_levels; ++i) {
        std::stringstream ss;
        Uint64 level_time_ms = final_game_stats.level_times[i];

        ss << "Level " << i + 1 << ": " << formatMillisecondsString(level_time_ms);
        drawText(300.0, 275.0 + (i * 45.0), 2.0, 1.0, ss.str());
    }
}

void drawTotalTime(bool should_display_time) {
    std::stringstream ss;
    ss << "TOTAL TIME: ";
    if (should_display_time) { ss << formatMillisecondsString(final_game_stats.total_time); }
    drawText(300.0, 750.0, 3.0, 1.0, ss.str());
}

// display the game stats in a timed manner
void executeGameSummaryAnimation() {

    Uint32 current_animation_time = SDL_GetTicks() - summary_animation_start_time;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white

    // check to see if summary animation timer is up
    if (current_animation_time >= 7000) {

        // update game state
        in_game_summary_animation = false;
        in_game_summary = true;
        still_game_summary_start_time = SDL_GetTicks();
        return;
    }

    // black screen for 1 second
    if (current_animation_time < 800) {
        return;
    }
    // make title text appear after 1 second
    else if (current_animation_time < 1300) {
        drawSummaryTitleText();
    }
    // make the death result text appear
    else if (current_animation_time < 2000) {
        drawSummaryTitleText();
        drawDeathResultText();
    }
    // show each time every quarter of a second
    else if (current_animation_time < 2250) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(1);
    }
    else if (current_animation_time < 2500) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(2);
    }
    else if (current_animation_time < 2750) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(3);
    }
    else if (current_animation_time < 3000) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(4);
    }
    else if (current_animation_time < 3250) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(5);
    }
    else if (current_animation_time < 3500) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(6);
    }
    else if (current_animation_time < 3750) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(7);
    }
    else if (current_animation_time < 4000) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(8);
    }
    else if (current_animation_time < 4250) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(9);
    }
    else if (current_animation_time < 5000) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(10);
    }
    else if (current_animation_time < 6000) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(10);
        drawTotalTime(false);
    }
    else if (current_animation_time < 7000) {
        drawSummaryTitleText();
        drawDeathResultText();
        drawLevelTimes(10);
        drawTotalTime(true);
    }
}

void drawEnterToContinueInfo() {
    Uint32 current_animation_time = SDL_GetTicks() - still_game_summary_start_time;

    // pulse in and out every 2 seconds
    if ((current_animation_time / 2000) % 2) {
        drawText(345.0, 850.0, 2.0, 1.0, "Press [ENTER] to return to menu.");
    }
}

void drawGameSummaryUI() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white

    drawSummaryTitleText();
    drawDeathResultText();
    drawLevelTimes(10);
    drawTotalTime(true);
    drawEnterToContinueInfo();
}

void drawGameMenu() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white

    drawText(300.0, 100.0, 6.0, 1.0, "GRID SNAPPER");
    drawSprite(250.0, 175.0, s_base_x2_texture, s_base_x2_texture_width, s_base_x2_texture_height);
    drawSprite(250.0, 375.0, m_texture, m_texture_width, m_texture_height);

    // draw menu option text
    if(selected_choice == MenuOption::PLAY) { SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); }
    drawText(270.0, 490, 2.0, 1.0, "> Play Game");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    if(selected_choice == MenuOption::SCORES) { SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); }
    drawText(270.0, 610, 2.0, 1.0, "> View High Scores");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    if(selected_choice == MenuOption::QUIT) { SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE); }
    drawText(270.0, 730, 2.0, 1.0, "> Quit Game");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    drawSprite(825.0, 700.0, c_x2_texture, c_x2_texture_width, c_x2_texture_height);
}

void drawRecordEntryUI() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white

    Uint32 current_animation_time = SDL_GetTicks() - record_entry_start_time;  

    string enter_record_text = "ENTER YOUR NAME: " + player_name;

    string blinking_underscore;
    blinking_underscore.resize(enter_record_text.size());
    for (int i = 0; i < blinking_underscore.size() - 1; ++i) {
        blinking_underscore[i] = ' ';
    }
    blinking_underscore[blinking_underscore.size() - 1] = '_';
    
    drawText(362.0, 100.0, 6.0, 1.0, "RECORD SET");
    drawSprite(350.0, 200.0, t_texture, t_texture_width, t_texture_height);

    drawText(275.0, 750.0, 1.5, 1.0, "Press [RIGHT] for next character and [ENTER] to submit");
    if ((current_animation_time / 1000) % 2) {
        drawText(385.0, 804.0, 2.0, 1.0, blinking_underscore);
    }
    drawText(385.0, 800.0, 2.0, 1.0, enter_record_text);
}

void drawHighScoresUI() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white
    
    if (!has_beat_snap && snap_lines_high_score_index < 12) {
        drawSprite(100.0, 700.0, s_speak_x2_texture, s_speak_x2_texture_width, s_speak_x2_texture_height);
        drawSprite(300.0, 650.0, db_texture, db_texture_width, db_texture_height);
        drawText(370.0, 711.0, 2.0, 1.0, snap_lines_high_score[snap_lines_high_score_index]);
    }
    else {
        drawSprite(750.0, 440.0, t_texture, t_texture_width, t_texture_height);
        drawSprite(-50.0, 440.0, t_texture, t_texture_width, t_texture_height);

    }

    drawText(204.0, 100.0, 5.0, 1.0, "Snapper Hall of Fame");
    for (int i = 0; i < top_times.size(); ++i) {
        std::stringstream ss;
        ss << (i + 1) << ": " << top_times[i].record_holder << " ----- " << formatMillisecondsString(top_times[i].time) << endl;
        drawText(395.0, (i * 75.0) + 250.0, 2.0, 1.0, ss.str());
    }

}


/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    if (in_game_menu) {
        drawGameMenu();
    }
    else if (in_game) {
        /* draw sprites */
        drawBackgroundSprite();
        drawPlayerSprite();
        drawObstaclesAndGoals();

        /* draw UI */
        drawUI();
    }
    else if (in_death_animation) {

        /* draw sprites */
        drawBackgroundSprite();
        drawObstaclesAndGoals();

        /* draw UI */
        drawUI();

        /* execute death animation */
        executeDeathAnimation();
    }
    else if (in_winning_animation) {

        /* draw sprites */
        drawBackgroundSprite();
        drawObstaclesAndGoals();

        /* draw UI */
        drawUI();

        /* execute winning animation */
        executeWinningAnimation();
    }
    else if (in_game_summary_animation) {
        executeGameSummaryAnimation();
    }
    else if (in_game_summary) {
        drawGameSummaryUI();
    }
    else if (in_record_entry) {
        drawRecordEntryUI();
    }
    else if (in_high_scores) {
        drawHighScoresUI();
    }

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(p_texture);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyTexture(o_texture);
    SDL_DestroyTexture(g_texture);
    SDL_DestroyTexture(d_texture);
    /* SDL will clean up the window/renderer for us. */
}