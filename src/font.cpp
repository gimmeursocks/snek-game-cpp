#include "font.h"
#include "font_data.h"
#include "logger.h"
#include <sstream>

const int fontSize = 22;
const SDL_Color textColor = {255, 255, 255, 255};

int Font::TTF_Fail() {
    Logger::LogError(TTF_GetError());
    return EXIT_FAILURE;
}

int Font::init(SDL_Renderer *renderer) {

    this->renderer = renderer;
    if (TTF_Init() != 0) {
        return TTF_Fail();
    }

    SDL_RWops *rw = SDL_RWFromConstMem(font_ttf, sizeof(font_ttf));
    this->font = TTF_OpenFontRW(rw, 1, fontSize);
    if (!this->font) {
        return TTF_Fail();
    }

    this->cacheInit();

    Logger::LogInfo("Font loaded successfully!");
    return EXIT_SUCCESS;
}

Font::~Font() {
    this->clearCache();
    if (this->font) {
        TTF_CloseFont(this->font);
    }

    TTF_Quit();
    Logger::LogInfo("Font closed successfully!");
}

void Font::cacheInit() {
    SDL_Color textColor = {255, 255, 255, 255};
    this->textCache[TITLE] = this->textToTexture("Snek", textColor);
    this->textCache[START] = this->textToTexture("'SPACE' to start", textColor);
    this->textCache[WASD] = this->textToTexture("use 'WASD' to control", textColor);
    this->textCache[QUIT_OR_RESTART] = this->textToTexture("'q' to quit, 'r' to restart", textColor);
}

TextureInfo *Font::getCache(CachedText cachedText) {
    return this->textCache[cachedText];
}

TextureInfo *Font::textToTexture(const char *text, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(this->font, text, color);
    if (!surface) {
        TTF_Fail();
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FRect rect = {0, 0, (float)surface->w, (float)surface->h};
    SDL_FreeSurface(surface);

    if (!texture) {
        TTF_Fail();
        return nullptr;
    }

    return new TextureInfo{texture, rect};
}

void Font::clearCache() {
    for (auto &text : this->textCache) {
        SDL_DestroyTextureInfo(text.second);
    }
    this->textCache.clear();
}

void SDL_DestroyTextureInfo(TextureInfo *textureInfo) {
    if (textureInfo) {
        if (textureInfo->texture) {
            SDL_DestroyTexture(textureInfo->texture);
        }
        delete textureInfo;
    }
}

void Font::renderCounter(TextureInfo **textureInfo, std::string text, int data) {
    if (*textureInfo) {
        SDL_DestroyTexture((*textureInfo)->texture);
    }

    std::stringstream ss;
    ss << text << data;
    // Logger::LogInfo(ss.str().c_str());
    *textureInfo = textToTexture(ss.str().c_str(), textColor);
}

void Font::renderMessage(TextureInfo **textureInfo, std::string text, int data) {
    std::stringstream ss;
    ss << text << data;
    // Logger::LogInfo(ss.str().c_str());
    *textureInfo = textToTexture(ss.str().c_str(), textColor);
}

void Font::renderFPSCounter(TextureInfo **textureInfo, int fps) {
    renderCounter(textureInfo, "FPS: ", fps);
}

void Font::renderScoreCounter(TextureInfo **textureInfo, int score) {
    renderCounter(textureInfo, "", score);
}

void Font::renderScoreMessage(TextureInfo **textureInfo, int score) {
    renderMessage(textureInfo, "Your Score is ", score);
}