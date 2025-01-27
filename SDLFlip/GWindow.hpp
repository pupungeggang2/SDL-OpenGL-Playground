#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void SWindowInit();
void SWindowLoop();
void SWindowMouse(float x, float y, int button);
void SWindowEnd();

void renderInit();
void render();
void renderAt(unsigned int texture, float texCoord[12], float x, float y, float w, float h);
