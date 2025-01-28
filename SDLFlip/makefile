linux: dummy
	clang++ *.cpp -o main -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU

mingw32: dummy
	clang++ *.cpp ../glades/src/glad.c -o main -I../glades/include -I../SDL2/include -lmingw32 -lopengl32 -lgdi32 -lSDL2main -lSDL2 -lSDL2_image -std=c++11 -w
	
dummy:
