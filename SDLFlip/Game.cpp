#include "Game.hpp"

std::vector<int> board;
std::vector<int> covered;
std::vector<int> exist;
bool clickable = false;
int clickTimeLeft = 0;
int clickNum = 0;
int clickA = -1;
int clickB = -1;

bool check = false;
int checkTime = 0;

void gameInit() {
    board = generateBoard();
    covered = {1, 1, 1, 1, 1, 1, 1, 1};
    exist = {1, 1, 1, 1, 1, 1, 1, 1};
}

std::vector<int> generateBoard() {
    std::vector<int> in = {1, 1, 2, 2, 3, 3, 4, 4};
    std::srand(std::time(0));
    std::vector<int> out = {};

    for (int i = 0; i < 8; i++) {
        int index = std::rand() % in.size();
        out.push_back(in[index]);
        in.erase(in.begin() + index);
    }

    return out;
}

void gameLoop() {
    if (clickable == false) {
        if (clickTimeLeft < 0) {
            clickTimeLeft = 0;
            clickable = true;
        } else {
            clickTimeLeft -= 25;
        }
    }
    
    if (check == true) {
        if (checkTime < 0) {
            checkTime = 0;
            check = false;
            checkTwoSame();
        } else {
            checkTime -= 25;
        }
    }
}

void checkTwoSame() {
    if (board[clickA] == board[clickB]) {
        exist[clickA] = 0;
        exist[clickB] = 0;
    }
    
    covered[clickA] = 1;
    covered[clickB] = 1;
    clickA = -1;
    clickB = -1;
}
