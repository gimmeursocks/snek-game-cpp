#include "render.h"
#include "logger.h"
#include "snake.h"
#include <format>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int TBPADDING = 60;
const int RLPADDING = 10;
const int GRID_HEIGHT = 30;
const int GRID_WIDTH = 30;

int RenderWindow::SDL_Fail() {
    Logger::LogError(SDL_GetError());
    return EXIT_FAILURE;
}

int RenderWindow::init() {

    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "system");

    if (SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_Fail();
    }

    this->window = SDL_CreateWindow("Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN);
    if (!this->window) {
        return SDL_Fail();
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
        return SDL_Fail();
    }

    Logger::LogInfo("Application started successfully!");
    return EXIT_SUCCESS;
}

void RenderWindow::clear() {
    SDL_SetRenderDrawColor(this->renderer, 100, 20, 30, 255);
    SDL_RenderClear(this->renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(this->renderer);
}

SDL_Renderer *RenderWindow::getRenderer() {
    return this->renderer;
}

RenderWindow::~RenderWindow() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
    }

    SDL_Quit();
    Logger::LogInfo("Application quit successfully!");
}

void RenderWindow::renderTextureInPosition(TextureInfo *textureInfo, TextureAnchor textureAnchor) {
    switch (textureAnchor) {
        case TOP_LEFT:
            textureInfo->rect.x = 0;
            textureInfo->rect.y = 0;
            break;
        case TOP_RIGHT:
            textureInfo->rect.x = static_cast<int>(WINDOW_WIDTH - textureInfo->rect.w);
            textureInfo->rect.y = 0;
            break;
        case BOTTOM_RIGHT:
            textureInfo->rect.x = static_cast<int>(WINDOW_WIDTH - textureInfo->rect.w);
            textureInfo->rect.y = static_cast<int>(WINDOW_HEIGHT - textureInfo->rect.h);
            break;
        case BOTTOM_LEFT:
            textureInfo->rect.x = 0;
            textureInfo->rect.y = static_cast<int>(WINDOW_HEIGHT - textureInfo->rect.h);
            break;
        case CENTER:
            textureInfo->rect.x = static_cast<int>((WINDOW_WIDTH - textureInfo->rect.w) / 2.0f);
            textureInfo->rect.y = static_cast<int>((WINDOW_HEIGHT - textureInfo->rect.h) / 2.0f);
            break;
        case CENTER_TOP:
            textureInfo->rect.x = static_cast<int>((WINDOW_WIDTH - textureInfo->rect.w) / 2.0f);
            textureInfo->rect.y = 0;
            break;
        case CENTER_BOTTOM:
            textureInfo->rect.x = static_cast<int>((WINDOW_WIDTH - textureInfo->rect.w) / 2.0f);
            textureInfo->rect.y = static_cast<int>(WINDOW_HEIGHT - textureInfo->rect.h);
            break;
        case NO_ANCHOR:
            break;
    }

    SDL_RenderCopyF(this->renderer, textureInfo->texture, NULL, &textureInfo->rect);
}

void RenderWindow::setColor(SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void RenderWindow::renderRect(const SDL_Rect &rect) {
    SDL_RenderDrawRect(this->renderer, &rect);
}

void RenderWindow::renderFRect(const SDL_FRect &rect) {
    SDL_RenderDrawRectF(this->renderer, &rect);
}

void RenderWindow::renderFillFRect(const SDL_FRect &rect) {
    SDL_RenderFillRectF(this->renderer, &rect);
}

void RenderWindow::renderFillRect(const SDL_Rect &rect) {
    SDL_RenderFillRect(this->renderer, &rect);
}

void RenderWindow::wrapAround(Point &object, const SDL_Rect &collider) {
    if (object.x < RLPADDING) {
        object.x = collider.w - GRID_WIDTH + RLPADDING;
    } else if (object.x + GRID_WIDTH > (collider.w + RLPADDING)) {
        object.x = RLPADDING;
    }

    if (object.y < TBPADDING) {
        object.y = collider.h - GRID_HEIGHT + TBPADDING;
    } else if (object.y + GRID_HEIGHT > (collider.h + TBPADDING)) {
        object.y = TBPADDING;
    }
}

void RenderWindow::renderSnake(Snake &snake) {
    renderSnakeBody(snake.head);
    for (auto& segment : snake.segments) {
        renderSnakeBody(segment);
    }
}

void RenderWindow::renderSnakeBody(Point &body) {
    SDL_Rect rect = {body.x, body.y, GRID_WIDTH, GRID_HEIGHT};
    renderFillRect(rect);
}

void RenderWindow::renderFood(Food &food) {
    setColor({255, 127, 156, 255});
    SDL_Rect foodRect = {food.position.x, food.position.y, GRID_WIDTH, GRID_HEIGHT};
    renderFillRect(foodRect);
    setColor({255, 255, 255, 255});
}
