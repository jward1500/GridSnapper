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

// general sdl variables used by everyone
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_FRect dst_rect;

// general game logic variables used by the UI
static bool inGame = true;
static Game game;
static Uint64 level_start_time;

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


#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900
#define MOVEMENT_JUMP 100;
constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 6;


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

    // this logic will change
    startLevel();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.scancode) {
        case SDL_SCANCODE_A:
            game.Move(MoveDirection::LEFT);
            break;
        case SDL_SCANCODE_W:
            game.Move(MoveDirection::UP);
            break;
        case SDL_SCANCODE_D:
            game.Move(MoveDirection::RIGHT);
            break;
        case SDL_SCANCODE_S:
            game.Move(MoveDirection::DOWN);
            break;
        }
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
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
    playerX = (float)game.pos.x * 100 + 100;
    playerY = (float)game.pos.y * 100 + 300;
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

// use game data to determine where the obstacle and the goal sprites should be drawn
void drawObstaclesAndGoals() {
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            Pos current_pos = { i, j };
            GridSpace current_space = game.GetGridSpace(current_pos);
            if (current_space == GridSpace::OBSTACLE) { drawObstacleSprite(current_pos); }
            else if (current_space == GridSpace::GOAL) { drawGoalSprite(current_pos); }
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
    drawText(100.0, 100.0, 2.0, 1.0, "Deaths: ");
}

void drawTimer() {

    // calculate seconds, tenths, and hundredths from total ms elapsed
    Uint64 time_elapsed_ms = SDL_GetTicks() - level_start_time;
    std::stringstream ss;


    // freeze and turn red after 1 minute
    if (time_elapsed_ms >= 59999) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // set color to red
        ss << "59:99";
    }
    else {
        int seconds = time_elapsed_ms / 1000;
        time_elapsed_ms -= seconds * 1000;
        int tenths = time_elapsed_ms / 100;
        time_elapsed_ms -= tenths * 100;
        int hundredths = time_elapsed_ms / 10;

        // format the time string with these calculated values
        string seconds_padding = seconds < 10 ? "0" : "";
        ss << seconds_padding << seconds << ":" << tenths << hundredths;
    }

    // draw the clock text
    drawText(505.0, 100.0, 5.0, 1.0, ss.str());
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color back to white
}

void drawLevelCounter() {
    drawText(1000.0, 100.0, 2.0, 1.0, "1/10");
}

void drawUI() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // set color to white
    drawDeathCounter();
    drawTimer();
    drawLevelCounter();
}


/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    /* draw sprites */
    drawBackgroundSprite();
    drawPlayerSprite();
    drawObstaclesAndGoals();

    /* draw UI */
    drawUI();

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
    /* SDL will clean up the window/renderer for us. */
}