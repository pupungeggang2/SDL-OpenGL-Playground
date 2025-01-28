#include "GWindow.hpp"
#include "Game.hpp"
#include "Physics.hpp"
#define FRAME_INTERVAL 25
#ifdef _WIN32
#define GL_CLAMP_TO_EDGE 0x812F
#endif
SDL_Window *window;
SDL_GLContext context;
SDL_Surface *sur;

int windowWidth = 640, windowHeight = 640;
bool running = true;
unsigned int frameCurrent, frameNext, delta, texture;

float UI[8][4] = {
    {64, 64, 128, 128}, {256, 64, 128, 128}, {448, 64, 128, 128}, {64, 256, 128, 128},
    {448, 256, 128, 128}, {64, 448, 128, 128}, {256, 448, 128, 128}, {448, 448, 128, 128}
};

float texCoord[5][12] = {
    {0.25, 1.0, 0.25, 0.5, 0.0, 1.0, 0.0, 1.0, 0.25, 0.5, 0.0, 0.5},
    {0.25, 0.5, 0.25, 0.0, 0.0, 0.5, 0.0, 0.5, 0.25, 0.0, 0.0, 0.0},
    {0.5, 0.5, 0.5, 0.0, 0.25, 0.5, 0.25, 0.5, 0.5, 0.0, 0.25, 0.0},
    {0.75, 0.5, 0.75, 0.0, 0.5, 0.5, 0.5, 0.5, 0.75, 0.0, 0.5, 0.0},
    {1.0, 0.5, 1.0, 0.0, 0.75, 0.5, 0.75, 0.5, 1.0, 0.0, 0.75, 0.0},
};

extern std::vector<int> board;
extern std::vector<int> covered;
extern std::vector<int> exist;
extern bool clickable;
extern int clickTimeLeft;
extern int clickNum;
extern int clickA;
extern int clickB;
extern bool check;
extern int checkTime;

void SWindowInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL Could not Initialize!" << std::endl;
        exit(0);
    } else {
        window = SDL_CreateWindow("Card Flip", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
        context = SDL_GL_CreateContext(window);
    }
    
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "SDL Could not Initialize PNG!" << std::endl;
        exit(0);
    }
    
    sur = IMG_Load("Texture.png");
}

void SWindowLoop() {
    while (running) {
        frameCurrent = SDL_GetTicks();
        frameNext = frameCurrent + FRAME_INTERVAL;
        delta = FRAME_INTERVAL;
    
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            
            if (event.type == SDL_MOUSEBUTTONUP) {
                SWindowMouse(event.button.x, event.button.y, event.button.button);
            }
        }
        
        gameLoop();
        render();
        SDL_GL_SwapWindow(window);
        
        frameCurrent = SDL_GetTicks();
        if (frameCurrent < frameNext) {
            SDL_Delay(frameNext - frameCurrent);
        }
    }
}

void SWindowMouse(float x, float y, int button) {
    if (button == 1) {
        if (clickable == true) {
            for (int i = 0; i < 8; i++) {
                if (pointInsideRect(x, y, UI[i])) {
                    if (exist[i] == 1) {
                        if (clickNum == 0) {
                            clickA = i;
                            clickNum = 1;
                            covered[i] = 0;
                        } else if (clickNum == 1) {
                            clickB = i;
                            clickNum = 0;
                            covered[i] = 0;
                            clickable = false;
                            clickTimeLeft = 1000;
                            check = true;
                            checkTime = 1000;
                        }
                    }
                }
            }
        }
    }
}

void SWindowEnd() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sur->w, sur->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sur->pixels);
    
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void render() {
    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY);
    
    for (int i = 0; i < 8; i++) {
        if (exist[i] == 1) {
            renderAt(texture, texCoord[board[i]], UI[i][0], UI[i][1], UI[i][2], UI[i][3]);
            if (covered[i] == 1) {
                renderAt(texture, texCoord[0], UI[i][0], UI[i][1], UI[i][2], UI[i][3]);
            }
        }
    }
}

void renderAt(unsigned int texture, float texCoord[12], float x, float y, float w, float h) {
    float v[12] = {
        x + w, y + h, x + w, y, x, y + h, x, y + h, x + w, y, x, y
    };
    glBindTexture(GL_TEXTURE_2D, texture);
    glVertexPointer(2, GL_FLOAT, 0, v);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
