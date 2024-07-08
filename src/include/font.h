#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

struct TextureInfo {
    SDL_Texture *texture;
    SDL_FRect rect;
};

enum CachedText {
    TITLE,
    START,
    WASD,
    QUIT_OR_RESTART
};

class Font {
private:
    std::unordered_map<CachedText, TextureInfo *> textCache;
    void clearCache();
    void cacheInit();
    SDL_Renderer *renderer;

public:
    TTF_Font *font;
    int TTF_Fail();
    int init(SDL_Renderer *);
    ~Font();
    TextureInfo *getCache(CachedText);
    TextureInfo *textToTexture(const char *, SDL_Color);
    void renderCounter(TextureInfo **, std::string, int);
    void renderMessage(TextureInfo **, std::string, int);
    void renderFPSCounter(TextureInfo **, int);
    void renderScoreCounter(TextureInfo **, int);
    void renderScoreMessage(TextureInfo **, int);
};

void SDL_DestroyTextureInfo(TextureInfo *textureInfo);