/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

bool init(); // Starts up SDL and creates window.
bool loadMedia(); // Loads the media.
void close(); // Frees media and shuts down SDL.

SDL_Surface* loadSurface(std::string path); // Loads individual image.
SDL_Window* gWindow = NULL; // Window to which we render.
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

bool init() {
  using namespace std;
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
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
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    cout << "Failed to load default image!\n"; success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_presses/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    cout << "Failed to load up image!\n"; success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_presses/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    cout << "Failed to load down image!\n"; success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_presses/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    cout << "Failed to load left image!\n"; success = false;
  }
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04_key_presses/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    cout << "Failed to load right image!\n"; success = false;
  }
  return success;
}

void close() {
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
    gKeyPressSurfaces[i] = NULL;
  }
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
  SDL_Surface* loaded = SDL_LoadBMP(path.c_str());
  if (loaded == NULL) {
    std::cout << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << "\n";
  }
  return loaded;
}

int main(int argc, char* args[]) {
  using namespace std;
  if (!init()) {
    cout << "Failed to init!\n";
  } else {
    if (!loadMedia()) {
      cout << "Failed to load media!\n";
    } else {
      bool quit = false;
      SDL_Event e;
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
      while(!quit) {
	while (SDL_PollEvent(&e) != 0) {
	  if (e.type == SDL_QUIT) quit = true;
	  else if (e.type == SDL_KEYDOWN) {
	    //Select surfaces based on key press
	    switch (e.key.keysym.sym) {
	    case SDLK_UP:
	      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
	      break;
	    case SDLK_DOWN:
	      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
	      break;
	    case SDLK_LEFT:
	      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
	      break;
	    case SDLK_RIGHT:
	      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
	      break;
	    default:
	      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
	      break;
	    }
	  }
	}
	SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface( gWindow );
      }
    }
  }
  close();
  return 0;
}
