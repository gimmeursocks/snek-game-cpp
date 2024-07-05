#include "game.h"

int main(int argc, char *argv[]) {
    Game game;
    if (game.init() != 0) {
        return EXIT_FAILURE;
    }
    game.run();
    game.cleanup();
    return EXIT_SUCCESS;
}