#include <graphics/batcher.h>
#include <graphics/window.h>
#include<game/game.h>
#include "TestGame.h"
using namespace engine;


int main(int argv, char** argc) {
    std::cout << "Entered main" << std::endl;

    Game::instance<TestGame>().setWindowSize(1280, 720);
    Game::instance<TestGame>().setTitle("Test");

    std::cout << "Prepared game loop" << std::endl;

    Game::instance<TestGame>().run();

    return EXIT_SUCCESS;
}