#include "render.h"
#include "constants.h"
#include "logger.h"
#include "snake.h"
#include <SDL2/SDL_image.h>
#include <format>

int RenderWindow::SDL_Fail() {
    Logger::LogError(SDL_GetError());
    return EXIT_FAILURE;
}

int RenderWindow::IMG_Fail() {
    Logger::LogError(IMG_GetError());
    return EXIT_FAILURE;
}

int RenderWindow::setIcon() {
    SDL_Surface *icon = IMG_Load(ICON_SRC);
    if (!icon) {
        return IMG_Fail();
    }
    SDL_SetWindowIcon(this->window, icon);
    SDL_FreeSurface(icon);

    Logger::LogInfo("Icon loaded successfully!");
    return EXIT_SUCCESS;
}

int RenderWindow::init() {
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "system");

    if (SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_Fail();
    }

    this->window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!this->window) {
        return SDL_Fail();
    }

    SDL_SetWindowMinimumSize(this->window, WINDOW_WIDTH, WINDOW_HEIGHT);

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
        return SDL_Fail();
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        return IMG_Fail();
    }

    if (setIcon() != 0) {
        return IMG_Fail();
    }

    Logger::LogInfo("Application started successfully!");
    return EXIT_SUCCESS;
}

void RenderWindow::clear() {
    setColor(BACKGROUND_COLOR);
    SDL_RenderClear(this->renderer);
}

void RenderWindow::display() {
    SDL_RenderPresent(this->renderer);
}

void RenderWindow::scale() {
    int currWindowWidth, currWindowHeight;
    SDL_GetWindowSize(this->window, &currWindowWidth, &currWindowHeight);

    float scaleX = (float)currWindowWidth / WINDOW_WIDTH;
    float scaleY = (float)currWindowHeight / WINDOW_HEIGHT;
    float scale = std::min(scaleX, scaleY);

    int offsetX = (currWindowWidth - WINDOW_WIDTH * scale) / 2;
    int offsetY = (currWindowHeight - WINDOW_HEIGHT * scale) / 2;

    SDL_Rect viewport = {offsetX, offsetY, static_cast<int>(WINDOW_WIDTH * scale), static_cast<int>(WINDOW_HEIGHT * scale)};

    SDL_RenderSetScale(this->renderer, scale, scale);
    SDL_RenderSetViewport(this->renderer, &viewport);
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

void RenderWindow::wrapAround(Point &object, const SDL_Rect &COLLIDER) {
    if (object.x < RLPADDING) {
        object.x = COLLIDER.w - GRID_WIDTH + RLPADDING;
    } else if (object.x + GRID_WIDTH > (COLLIDER.w + RLPADDING)) {
        object.x = RLPADDING;
    }

    if (object.y < TBPADDING) {
        object.y = COLLIDER.h - GRID_HEIGHT + TBPADDING;
    } else if (object.y + GRID_HEIGHT > (COLLIDER.h + TBPADDING)) {
        object.y = TBPADDING;
    }
}

void RenderWindow::renderSnake(Snake &snake) {
    renderSnakeBody(snake.head);
    for (auto &segment : snake.segments) {
        renderSnakeBody(segment);
    }
}

void RenderWindow::renderSnakeBody(Point &body) {
    SDL_Rect rect = {body.x, body.y, GRID_WIDTH, GRID_HEIGHT};
    renderFillRect(rect);
}

void RenderWindow::renderFood(Food &food) {
    setColor(FOOD_COLOR);
    SDL_Rect foodRect = {food.position.x, food.position.y, GRID_WIDTH, GRID_HEIGHT};
    renderFillRect(foodRect);
    setColor(TEXT_COLOR);
}
