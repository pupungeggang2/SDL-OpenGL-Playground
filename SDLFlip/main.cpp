#include "Game.hpp"
#include "GWindow.hpp"

int main() {
    gameInit();
    SWindowInit();
    renderInit();
    SWindowLoop();
    SWindowEnd();
    return 0;
}
