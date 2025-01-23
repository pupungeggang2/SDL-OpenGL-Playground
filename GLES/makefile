build: dummy
	clang++ main.cpp ../glades/src/glad.c -o main -I../glades/include -lglfw -lSDL2 -lSDL2main -w

mingw32: dummy
	clang++ main.cpp ../glades/src/glad.c ../GLFW/lib/libglfw3.a -o main -I../glades/include -I../GLFW/include -I../SDL2/include -lmingw32 -lgdi32 -lSDL2main -lSDL2 -std=c++11 -w

dummy:
