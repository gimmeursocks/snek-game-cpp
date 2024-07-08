#pragma once

#include <SDL2/SDL.h>

// Game
const char *const GAME_NAME = "Snek";

// Icon Path
const char *const ICON_SRC = "src/assets/icon.png";

// Window dimensions
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// Padding
const int TBPADDING = 60;
const int RLPADDING = 10;

// Grid dimensions
const int GRID_HEIGHT = 30;
const int GRID_WIDTH = 30;

// Colors
const SDL_Color TEXT_COLOR = {255, 255, 255, 255};
const SDL_Color BACKGROUND_COLOR = {100, 20, 30, 255};
const SDL_Color FOOD_COLOR = {255, 127, 156, 255};

// Font size
const int FONT_SIZE = 22;

// Collider
const SDL_Rect COLLIDER = {RLPADDING, TBPADDING, WINDOW_WIDTH - 2 * RLPADDING, WINDOW_HEIGHT - 2 * TBPADDING};

// Movement
const int INPUT_INTERVAL = 150;
const int MOVE_SPEED = 130;