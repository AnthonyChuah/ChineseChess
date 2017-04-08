/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture {
public:
  LTexture();
  ~LTexture();
  bool loadFromFile( std::string path );
  bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
  void free();
  void setColor( Uint8 red, Uint8 green, Uint8 blue );
  void setBlendMode( SDL_BlendMode blending );
  void setAlpha( Uint8 alpha );
  void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
  int getWidth();
  int getHeight();
private:
  //The actual hardware texture
  SDL_Texture* mTexture;
  int mWidth;
  int mHeight;
};

bool init();
bool loadMedia();
void close();
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Globally used font
TTF_Font *gFont = NULL;
//Rendered texture
LTexture gTextTexture;

LTexture::LTexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  free();
}

bool LTexture::loadFromFile( std::string path ) {
  free();
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == NULL ) {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  } else {
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    //Create texture from surface pixels
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
  mTexture = newTexture;
  return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor ) {
  free();
  //Render text surface: gFont is global Font setting
  SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
  if( textSurface == NULL )
    {
      printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
  else
    {
      //Create texture from surface pixels
      mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
      if( mTexture == NULL )
	{
	  printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
	}
      else
	{
	  //Get image dimensions
	  mWidth = textSurface->w;
	  mHeight = textSurface->h;
	}
      //Get rid of old surface
      SDL_FreeSurface( textSurface );
    }
  //Return success
  return mTexture != NULL;
}

void LTexture::free() {
  //Free texture if it exists
  if( mTexture != NULL ) {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
  //Modulate texture rgb
  SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ) {
  //Set blending function
  SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ) {
  //Modulate texture alpha
  SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  //Set clip rendering dimensions
  if( clip != NULL ) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  //Render to screen
  SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }

bool init() {
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
	  //Create vsynced renderer for window
	  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	  if( gRenderer == NULL )
	    {
	      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	      success = false;
	    }
	  else
	    {
	      //Initialize renderer color
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	      //Initialize PNG loading
	      int imgFlags = IMG_INIT_PNG;
	      if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
		  printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		  success = false;
		}
	      //Initialize SDL_ttf
	      if( TTF_Init() == -1 )
		{
		  printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
  //Open the font
  gFont = TTF_OpenFont( "Helvetica.ttf", 28 );
  if( gFont == NULL )
    {
      printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
      success = false;
    }
  else
    {
      //Render text
      SDL_Color textColor = { 0, 0, 0 };
      if( !gTextTexture.loadFromRenderedText( "The quick brown fox jumps over the lazy dog", textColor ) )
	{
	  printf( "Failed to render text texture!\n" );
	  success = false;
	}
    }
  return success;
}

void close() {
  gTextTexture.free();
  TTF_CloseFont( gFont );
  gFont = NULL;
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int main( int argc, char* args[] )
{
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
	      //Clear screen
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	      SDL_RenderClear( gRenderer );
	      //Render current frame
	      gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
	      //Update screen
	      SDL_RenderPresent( gRenderer );
	    }
	}
    }
  //Free resources and close SDL
  close();
  return 0;
}