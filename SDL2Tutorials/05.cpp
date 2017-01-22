/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gStretchedSurface = NULL;

bool init() {
  using namespace std;
  bool success = true;
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not init! SDL Error: " << SDL_GetError() << "\n";
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  gStretchedSurface = loadSurface("05_optimized/stretch.bmp");
  if (gStretchedSurface == NULL) {
    std::cout << "Failed to load stretching image!\n";
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gStretchedSurface);
  gStretchedSurface = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
  using namespace std;
  SDL_Surface* opt = NULL;
  SDL_Surface* loaded = SDL_LoadBMP(path.c_str());
  if (loaded == NULL) { 
   cout << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << "\n";
  } else {
    opt = SDL_ConvertSurface(loaded, gScreenSurface->format, 0); // Stretches image.
    // The third arg should be 0, not NULL. This was SDL 1.2 feature, no longer used.
    if (opt == NULL) {
      cout << "Unable to optimize image " << path << "! SDL Error: " << SDL_GetError() << "\n";
    }
    SDL_FreeSurface(loaded);
  }
  return opt;
}

int main(int argc, char* args[]) {
  using namespace std;
  if( !init() ) {
    cout << "Failed to init!\n";
  } else {
    if(!loadMedia()) {
      cout << "Failed to load media!\n";
    } else {
      bool quit = false;
      SDL_Event e;
      while (!quit) {
	while (SDL_PollEvent(&e) != 0) {
	  if (e.type == SDL_QUIT) {
	    quit = true;
	  }
	}
	SDL_Rect stretchRect; // Makes a rectangle.
	stretchRect.x = 0; // Location x and ycoords.
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
	// BlitScaled instead of BlitSurface, can scale image to fit the rectangle.
	SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();
  return 0;
}
