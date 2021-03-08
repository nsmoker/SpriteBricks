#include <graphics/batcher.h>
#include <graphics/window.h>
#include<game/game.h>
#include "TestGame.h"
using namespace engine;


int main() {
    TestGame game(1280, 720, "Test");
    game.run();
}