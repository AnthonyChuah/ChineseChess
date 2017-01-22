/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(); // Starts up SDL and creates Window.
bool loadMedia(); // Loads media.
void close(); // Frees media and shuts down SDL.

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gXOut = NULL;

bool init() {
  using namespace std;
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  using namespace std;
  bool success = true;
  gXOut = SDL_LoadBMP("x.bmp");
  if (gXOut == NULL) {
    cout << "Unable to load image x.bmp! SDL Error: " << SDL_GetError() << "\n";
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gXOut); // Deallocates surface.
  gXOut = NULL;
  SDL_DestroyWindow(gWindow); // Frees Window memory.
  gWindow = NULL;
  SDL_Quit(); // Quits SDL subsystems.
}

int main(int argc, char* args[]) {
  using namespace std;
  if (!init()) {
    cout << "Failed to initialize!\n";
  } else {
    if (!loadMedia()) {
      cout << "Failed to load media!\n";
    } else {
      bool quit = false;
      SDL_Event e; // This is an event handler.
      while (!quit) {
	// SDL stores events (mouse clicks, keypresses, etc.) into an EVENT QUEUE.
	// SDL_PollEvent will pop MOST RECENT event off the queue.
	while (SDL_PollEvent(&e) != 0) {
	  if (e.type == SDL_QUIT) {
	    // User requests QUIT.
	    quit = true;
	  }
	}
	SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();
  return 0;
}
