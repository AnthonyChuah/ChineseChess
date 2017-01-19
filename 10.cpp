/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture {
public:
  LTexture();
  ~LTexture();
  bool loadFromFile( std::string path );
  //Deallocates texture (why separate from destructor? so you can load new ones to overwrite)
  void free();
  //Renders texture at given point
  void render( int x, int y );
  int getWidth();
  int getHeight();
private:
  //The actual hardware texture
  SDL_Texture* mTexture;
  //Image dimensions
  int mWidth;
  int mHeight;
};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gFooTexture;
LTexture gBackgroundTexture;

LTexture::LTexture() : mTexture(NULL), mWidth(0), mHeight(0) {}
LTexture::~LTexture() { free(); }
bool LTexture::loadFromFile( std::string path ) {
  free();
  //The final texture
  SDL_Texture* newTexture = NULL;
  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == NULL )
    {
      printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
  else
    {
      //Color key image. 0 FF FF is cyan, the background of that image.
      SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
      //Create texture from surface pixels. Renderer turns a Surface into a Texture.
      newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
      if( newTexture == NULL ) {
	printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
      } else {
	//Get image dimensions
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
      }
      //Get rid of old loaded surface
      SDL_FreeSurface( loadedSurface );
    }
  //Return success
  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free() {
  if( mTexture != NULL ) {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::render( int x, int y ) {
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
  // SDL_RenderCopy renders the mTexture (image) into the quadrant specified in renderQuad.
  // The renderer is the global gRenderer.
}

int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }

bool init() {
  bool success = true;
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
      gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
	{
	  printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
	}
      else
	{
	  //Create renderer for window
	  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	  if( gRenderer == NULL )
	    {
	      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	      success = false;
	    }
	  else
	    {
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
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
  bool success = true;
  if( !gFooTexture.loadFromFile( "10_color_keying/foo.png" ) )
    {
      printf( "Failed to load Foo' texture image!\n" );
      success = false;
    }
  if( !gBackgroundTexture.loadFromFile( "10_color_keying/background.png" ) )
    {
      printf( "Failed to load background texture image!\n" );
      success = false;
    }
  return success;
}

void close() {
  gFooTexture.free();
  gBackgroundTexture.free();
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

int main( int argc, char* args[] ) {
  if( !init() )
    {
      printf( "Failed to initialize!\n" );
    }
  else
    {
      if( !loadMedia() )
	{
	  printf( "Failed to load media!\n" );
	}
      else
	{	
	  bool quit = false;
	  SDL_Event e;
	  int x_pos = 0, y_pos = 0;
	  while( !quit )
	    {
	      while( SDL_PollEvent( &e ) != 0 )
		{
		  if( e.type == SDL_QUIT )
		    {
		      quit = true;
		    }
		}
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); // White, Opaque
	      SDL_RenderClear( gRenderer ); // Clear screen.
	      //Render background texture to screen
	      gBackgroundTexture.render( 0, 0 );
	      //Render Foo' to the screen at position 240, 190.
	      gFooTexture.render( x_pos, y_pos ); // Remember that this writes to the gRenderer.
	      //Update screen
	      SDL_RenderPresent( gRenderer );
	      ++x_pos; ++y_pos;
	      if (x_pos >= SCREEN_WIDTH) x_pos = 0;
	      if (y_pos >= SCREEN_HEIGHT) y_pos = 0;
	    }
	}
    }
  close();
  return 0;
}
