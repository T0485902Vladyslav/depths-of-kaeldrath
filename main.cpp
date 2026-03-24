#include <cstdlib>
#include <ctime>
#include "GameManager.h"

int main() {
    srand(time(0));
    GameManager game;
    game.run();
    return 0;
}