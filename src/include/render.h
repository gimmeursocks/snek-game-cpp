#pragma once

#include "font.h"

enum TextureAnchor {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER,
    CENTER_TOP,
    CENTER_BOTTOM,
    NO_ANCHOR
};

struct TextureInfo;
class Food;
class Point;
class Snake;

class RenderWindow {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int SDL_Fail();
    int IMG_Fail();
    int setIcon();

public:
    ~RenderWindow();
    int init();
    void clear();
    void display();
    void scale();
    SDL_Renderer *getRenderer();
    void renderTextureInPosition(TextureInfo *, TextureAnchor);
    void setColor(SDL_Color);
    void renderRect(const SDL_Rect &);
    void renderFRect(const SDL_FRect &);
    void renderFillRect(const SDL_Rect &);
    void renderFillFRect(const SDL_FRect &);
    void wrapAround(Point &, const SDL_Rect &);
    void renderSnake(Snake &);
    void renderSnakeBody(Point &);
    void renderFood(Food &);
};