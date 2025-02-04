build: dummy
	clang++ main.cpp ../glad/src/glad.c -o main -I../glad/include -lglfw -lSDL2 -lSDL2main -w

mingw32: dummy
	clang++ main.cpp ../glad/src/glad.c ../GLFW/lib/libglfw3.a -o main -I../glad/include -I../GLFW/include -I../SDL2/include -lmingw32 -lgdi32 -lSDL2main -lSDL2 -std=c++11 -w

mac: dummy
	clang++ main.cpp ../glad/src/glad.c ../GLFW/lib-arm64/libglfw3.a -o main -I../glad/include -I../GLFW/include -framework Cocoa -framework IOKit -lSDL2 -std=c++11 -w

mac2: dummy
	clang++ main.cpp ../glad/src/glad.c /opt/homebrew/lib/libglfw3.a -o main -I../glad/include -I/opt/homebrew/include -framework Cocoa -framework IOKit -lSDL2 -std=c++11 -w

dummy:
