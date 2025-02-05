build: dummy
	clang++ main.cpp ../glad/src/glad.c -o main -I../glad/include -lglfw -lSDL2 -w

mingw32: dummy
	clang++ main.cpp ../glad/src/glad.c -o main -I../glad/include -lmingw32 -lSDL2main -lSDL2 -std=c++11 -w

mac: dummy
	clang++ main.cpp ../glad/src/glad.c -o main -I../glad/include -framework Cocoa -framework IOKit -lSDL2 -std=c++11 -w

dummy: