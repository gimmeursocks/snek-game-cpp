#pragma once

#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern const SDL_Rect collider;

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Game {
private:
    RenderWindow window;
    Font font;
    bool running = true;
    bool mainMenu = true;
    bool gameOver = false;
    int score = 0;
    int oldScore = 0;
    int fps = 0;
    int frames = 0;
    int lastSavedTime = 0;
    int lastFrameTime = 0;
    int lastDirTime = 0;
    int lastMoveTime = 0;
    const int MOVE_INTERVAL = 160;
    const int MOVE_SPEED = 150;
    TextureInfo *fpsCounterTexture = nullptr;
    TextureInfo *scoreCounterTexture = nullptr;
    TextureInfo *scoreMessageTexture = nullptr;
    Direction currentDirection = NONE;
    Direction nextDirection = NONE;
    void handleInput();
    void update();
    void render();
    void restart();
    void endGame();

public:
    int init();
    void run();
    void cleanup();
};
