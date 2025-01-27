#include "Physics.hpp"

bool pointInsideRect(float x, float y, float rect[4]) {
    return x > rect[0] && x < rect[0] + rect[2] && y > rect[1] && y < rect[1] + rect[3];
}
