http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php


g++ 01_hello_SDL.cpp -IC:\MinGW-W64\mingw64\include\SDL2 -LC:\MinGW-W64\mingw64\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o 01_hello_SD

g++ 01_hello_SDL.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o 01_hello_SDL