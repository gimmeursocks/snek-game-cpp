#include "game.h"
#include "logger.h"
#include "snake.h"
#include <format>

const SDL_Rect collider = {RLPADDING, TBPADDING, WINDOW_WIDTH - 2 * RLPADDING, WINDOW_HEIGHT - 2 * TBPADDING};
Snake snake;

int Game::init() {
    snake.init();

    if (window.init() != 0) {
        return EXIT_FAILURE;
    }
    if (font.init(window.getRenderer()) != 0) {
        return EXIT_FAILURE;
    }

    font.renderScoreCounter(&scoreCounterTexture, 0);
    return EXIT_SUCCESS;
}

void Game::run() {
    while (running) {
        handleInput();
        if (!mainMenu && !gameOver) {
            update();
        }
        render();
    }
}

void Game::cleanup() {
    SDL_DestroyTextureInfo(fpsCounterTexture);
    SDL_DestroyTextureInfo(scoreCounterTexture);
    SDL_DestroyTextureInfo(scoreMessageTexture);
}

void Game::restart() {
    mainMenu = true;
    gameOver = false;
    score = 0;
    oldScore = 0;
    font.renderScoreCounter(&scoreCounterTexture, 0);
    snake.reset();
    currentDirection = NONE;
    nextDirection = NONE;
}

void Game::endGame() {
    gameOver = true;
    font.renderScoreMessage(&scoreMessageTexture, score);
}

void Game::handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            Logger::Log(std::format("Key pressed: {}", SDL_GetKeyName(e.key.keysym.sym)));
            if (mainMenu) {
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        mainMenu = false;
                        break;
                    default:
                        break;
                }
            } else if (gameOver) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        running = false;
                        break;
                    case SDLK_r:
                        restart();
                        break;
                    default:
                        break;
                }
            } else {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        nextDirection = UP;
                        break;
                    case SDLK_a:
                        nextDirection = LEFT;
                        break;
                    case SDLK_s:
                        nextDirection = DOWN;
                        break;
                    case SDLK_d:
                        nextDirection = RIGHT;
                        break;
                    default:
                        break;
                }
            }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                Logger::Log(std::format("Left mouse button clicked at ({}, {})", e.button.x, e.button.y));
            } else if (e.button.button == SDL_BUTTON_RIGHT) {
                Logger::Log(std::format("Right mouse button clicked at ({}, {})", e.button.x, e.button.y));
            } else if (e.button.button == SDL_BUTTON_MIDDLE) {
                Logger::Log(std::format("Middle mouse button clicked at ({}, {})", e.button.x, e.button.y));
            }
        }
    }
}

void Game::update() {
    int currentTime = SDL_GetTicks();

    lastFrameTime = currentTime;
    frames++;
    if (currentTime > lastSavedTime + 1000) {
        fps = frames;
        frames = 0;
        lastSavedTime = currentTime;
        font.renderFPSCounter(&fpsCounterTexture, fps);
    }

    if (score != oldScore) {
        oldScore = score;
        font.renderScoreCounter(&scoreCounterTexture, score);
    }

    if (currentTime > lastDirTime + MOVE_INTERVAL) {

        lastDirTime = currentTime;

        if (nextDirection != NONE) {
            // avoiding a 180 degree turn
            if (currentDirection == NONE ||
                (currentDirection == UP && nextDirection != DOWN) ||
                (currentDirection == DOWN && nextDirection != UP) ||
                (currentDirection == LEFT && nextDirection != RIGHT) ||
                (currentDirection == RIGHT && nextDirection != LEFT)) {
                currentDirection = nextDirection;
            }
            nextDirection = NONE;
        }
    }

    if (currentTime > lastMoveTime + MOVE_SPEED) {

        lastMoveTime = currentTime;
        snake.move(currentDirection);

        if (snake.checkSelfCollision()) {
            endGame();
        } else {
            window.wrapAround(snake.head, collider);
            if (snake.checkFoodCollision()) {
                score++;
                snake.grow();
            }
        }
    }
}

void Game::render() {
    window.clear();
    if (mainMenu) {
        window.renderTextureInPosition(font.getCache(TITLE), CENTER);
        window.renderTextureInPosition(font.getCache(START), BOTTOM_LEFT);
        window.renderTextureInPosition(font.getCache(WASD), BOTTOM_RIGHT);
    } else if (gameOver) {
        window.renderTextureInPosition(font.getCache(TITLE), CENTER_TOP);
        window.renderTextureInPosition(scoreMessageTexture, CENTER);
        window.renderTextureInPosition(font.getCache(QUIT_OR_RESTART), BOTTOM_RIGHT);
    } else {
        window.renderTextureInPosition(font.getCache(TITLE), CENTER_TOP);
        if (fpsCounterTexture) {
            window.renderTextureInPosition(fpsCounterTexture, TOP_RIGHT);
        }
        if (scoreCounterTexture) {
            window.renderTextureInPosition(scoreCounterTexture, BOTTOM_RIGHT);
        }
        window.setColor(textColor);
        window.renderSnake(snake);
        window.renderRect(collider);
        window.renderFood(snake.food);
    }

    window.display();
}
