#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void SWindowInit();
void SWindowLoop();
void SWindowMouse(float x, float y, int button);
void SWindowEnd();

void renderInit();
void render();
void renderAt(SDL_Surface *sur, float texCoord[12], float x, float y, float w, float h);
