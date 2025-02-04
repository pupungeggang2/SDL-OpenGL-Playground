linux: dummy
	clang++ *.cpp ../glad/src/glad.c -o main -I../glad/include -lSDL2 -lSDL2_image -lSDL2_ttf

mingw32: dummy
	clang++ *.cpp ../glades/src/glad.c -o main -I../glades/include -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11 -w

mac: dummy
	clang++ *.cpp ../glad/src/glad.c -o main -I../glad/include -I../SDL2.framework/Headers -I../SDL2_image.framework/Headers -I../SDL2_ttf.framework/Headers -framework Cocoa -framework IOKit -F .. -framework SDL2 -framework SDL2_image -framework SDL2_ttf -rpath .. -std=c++11 -w

mac-brew: dummy
	clang++ *.cpp ../glad/src/glad.c -o main -I/opt/homebrew/include -L/opt/homebrew/lib -I../glad/include -lSDL2 -lSDL2_image -lSDL2_ttf -std=c++11 -w

dummy:
