#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>

const char* vertexShaderSource = R"(#version 300 es
    in vec4 a_position;
    in vec3 a_color;
    uniform vec3 u_rotate;
    uniform mat4 u_mat;
    out vec3 p_color;
    
    void getRotate(in vec3 rot, out mat4 rotation_mat) {
        float sx = sin(rot.x);
        float sy = sin(rot.y);
        float sz = sin(rot.z);
        float cx = cos(rot.x);
        float cy = cos(rot.y);
        float cz = cos(rot.z);

        mat4 rot_x = mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cx, -sx, 0.0,
            0.0, sx, cx, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 rot_y = mat4(
            cy, 0.0, sy, 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sy, 0.0, cy, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
        mat4 rot_z = mat4(
            cz, -sz, 0.0, 0.0,
            sz, cz, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );

        rotation_mat = rot_z * rot_y * rot_x * mat4(1.0);
    }
    
    void main() {
        mat4 rotation_mat = mat4(1.0);
        getRotate(u_rotate, rotation_mat);
        gl_Position = rotation_mat * a_position;
        p_color = a_color;
    }
)";

const char* fragmentShaderSource = R"(#version 300 es
    precision highp float;
    in vec3 p_color;
    out vec4 outColor;
    void main() {
        outColor = vec4(p_color, 1.0);
    }
)";

unsigned int frameCurrent = 0;
unsigned int frameNext = 0;
int delta = 0;
float rx = 0, ry = 0, rz = 0;
bool running = true;
SDL_Window *window;
SDL_GLContext context;

int main(int argc, char* argv[]) {
    // Data
    float vertices[18] = {
        0.0, 0.5, 0.0, 1.0, 0.0, 0.0,
        -0.433, -0.25, 0.0, 0.0, 1.0, 0.0,
        0.433, -0.25, 0.0, 0.0, 0.0, 1.0
    };

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Triangle Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);
   
    gladLoadGLES2Loader(SDL_GL_GetProcAddress);
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Var
    float m[16] = {
        0.5, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    GLint luMat = glGetUniformLocation(shaderProgram, "u_mat");
    GLint luRot = glGetUniformLocation(shaderProgram, "u_rotate");
    GLint laColor = glGetAttribLocation(shaderProgram, "a_color");
    GLint laPosition = glGetAttribLocation(shaderProgram, "a_position");
    GLuint vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(laPosition, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(laPosition);
    glVertexAttribPointer(laColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(laColor);

    while (running) {
        frameCurrent = SDL_GetTicks();
        frameNext = frameCurrent + 25;
        delta = 25;
        rz += delta / 1000.0;
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLineWidth(2);
        
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(luMat, 1, GL_FALSE, m);
        glUniform3f(luRot, rx, ry, rz);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //std::cout << SDL_GetTicks() - frameCurrent << std::endl;
        SDL_GL_SwapWindow(window);
        
        frameCurrent = SDL_GetTicks();
        if (frameCurrent < frameNext) {
            SDL_Delay(frameNext - frameCurrent);
        }
    }

    return 0;
}
