#include <graphics/batcher.h>
#include <graphics/window.h>
#include<game/game.h>
#include "TestGame.h"
using namespace engine;


int main(int argv, char** argc) {
    std::cout << "Entered main" << std::endl;

    TestGame game(1280, 720, "Test");

    std::cout << "Prepared game loop" << std::endl;

    game.run();

    return EXIT_SUCCESS;
}