#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#ifdef NDEBUG
    #define DEBUG 0
#else
    #define DEBUG 1
#endif

class Logger {
public:
    static void Log(const std::string &message) {
        if (DEBUG) {
            std::cout << message << '\n';
        }
    }

    static void LogInfo(const std::string &message) {
        if (DEBUG) {
            SDL_Log("%s", message.c_str());
        }
    }

    static void LogError(const std::string &message) {
        if (DEBUG) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", message.c_str());
        }
    }
};