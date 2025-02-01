#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <glad/glad.h>
#ifdef __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

void SWindowInit();
void SWindowLoop();
void SWindowMouse(float x, float y, int button);
void SWindowEnd();

void renderInit();
void render();
void renderAt(SDL_Surface *sur, float texCoord[12], float x, float y, float w, float h);
