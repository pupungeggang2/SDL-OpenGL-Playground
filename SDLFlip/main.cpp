#include "Game.hpp"
#include "GWindow.hpp"

int main(int argc, char *argv[]) {
    gameInit();
    SWindowInit();
    renderInit();
    SWindowLoop();
    SWindowEnd();
    return 0;
}
