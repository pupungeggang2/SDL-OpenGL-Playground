#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Triangle Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    std::cout << glGetString(GL_VERSION) << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(320.0f, 50.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(540.0f, 430.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(100.0f, 430.0f);
        glEnd();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}