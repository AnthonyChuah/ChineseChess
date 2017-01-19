/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture( std::string path );

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init() {
  //Initialization flag
  bool success = true;
  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
  else
    {
      //Set texture filtering to linear
      if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
	  printf( "Warning: Linear texture filtering not enabled!" );
	}
      //Create window
      gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
	{
	  printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
	}
      else
	{
	  // NEW: create renderer. Notice flag SDL_RENDERER_ACCELERATED. Hardware accelerated.
	  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	  if( gRenderer == NULL )
	    {
	      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	      success = false;
	    }
	  else
	    {
	      //Initialize renderer color to white opaque.
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	      //Initialize PNG loading
	      int imgFlags = IMG_INIT_PNG;
	      if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
		  printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		  success = false;
		}
	    }
	}
    }
  return success;
}

bool loadMedia() {
  //Loading success flag
  bool success = true;
  //Load PNG texture
  gTexture = loadTexture( "07_texture/texture.png" );
  if( gTexture == NULL )
    {
      printf( "Failed to load texture image!\n" );
      success = false;
    }
  return success;
}

void close() {
  //Free loaded image
  SDL_DestroyTexture( gTexture );
  gTexture = NULL;
  //Destroy window and renderer
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

/* Textures in SDL have their own data type called SDL_Texture. When you deal with them,
you need an SDL_Renderer to render it to the screen. That's why we declare a global renderer
called gRenderer. */
SDL_Texture* loadTexture( std::string path ) {
  //The final texture
  SDL_Texture* newTexture = NULL;
  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); // Same as prev tute.
  if( loadedSurface == NULL )
    {
      printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
  else
    {
      // NEW: creates texture from surface.
      newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
      if( newTexture == NULL )
	{
	  printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
      // NEW: no longer need the old surface, so free it.
      SDL_FreeSurface( loadedSurface );
    }
  return newTexture;
}

int main( int argc, char* args[] ) {
  //Start up SDL and create window
  if( !init() )
    {
      printf( "Failed to initialize!\n" );
    }
  else
    {
      //Load media
      if( !loadMedia() )
	{
	  printf( "Failed to load media!\n" );
	}
      else
	{	
	  //Main loop flag
	  bool quit = false;
	  //Event handler
	  SDL_Event e;
	  //While application is running
	  while( !quit )
	    {
	      //Handle events on queue
	      while( SDL_PollEvent( &e ) != 0 )
		{
		  //User requests quit
		  if( e.type == SDL_QUIT )
		    {
		      quit = true;
		    }
		}
	      //Fills screen with color last set by SDL_SetRenderDrawColor.
	      SDL_RenderClear( gRenderer );
	      //Render texture to screen
	      SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
	      //Update screen
	      SDL_RenderPresent( gRenderer );
	      // Equivalent to SDL_UpdateWindowSurface but with Renderers.
	    }
	}
    }
  //Free resources and close SDL
  close();
  return 0;
}
