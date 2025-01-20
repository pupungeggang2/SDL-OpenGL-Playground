build: dummy
	clang++ main.cpp glad/src/glad.c -o main -Iglad/include -lglfw -lSDL2 -lSDL2main

mingw32: dummy
	clang++ main.cpp glad/src/glad.c GLFW/lib/libglfw3.a -o main -Iglad/include -IGLFW/include -ISDL2/include -lmingw32 -lgdi32 -lSDL2main -lSDL2 -std=c++11 -w

dummy:

