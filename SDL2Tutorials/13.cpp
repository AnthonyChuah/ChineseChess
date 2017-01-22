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
  void free();
  void setColor( Uint8 red, Uint8 green, Uint8 blue );
  void setBlendMode( SDL_BlendMode blending );
  void setAlpha( Uint8 alpha );
  void render( int x, int y, SDL_Rect* clip = NULL );
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
LTexture gModulatedTexture;
LTexture gBackgroundTexture;

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
    //Color key image
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
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

void LTexture::free() {
  if( mTexture != NULL ) {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
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

void LTexture::render( int x, int y, SDL_Rect* clip ) {
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  //Set clip rendering dimensions
  if( clip != NULL ) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  //Render to screen
  SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }

bool init() {
  bool success = true;
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  } else {
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
      printf( "Warning: Linear texture filtering not enabled!" );
    }
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    } else {
      //Create renderer for window
      gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
      if( gRenderer == NULL ) {
	printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	success = false;
      } else {
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
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
  //Load front alpha texture
  if( !gModulatedTexture.loadFromFile( "13_alpha_blending/fadeout.png" ) ) {
    printf( "Failed to load front texture!\n" );
    success = false;
  } else {
    //Set standard alpha blending
    gModulatedTexture.setBlendMode( SDL_BLENDMODE_BLEND );
  }
  //Load background texture
  if( !gBackgroundTexture.loadFromFile( "13_alpha_blending/fadein.png" ) ) {
    printf( "Failed to load background texture!\n" );
    success = false;
  }
  return success;
}

void close() {
  gModulatedTexture.free();
  gBackgroundTexture.free();
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
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

			//Modulation component
			Uint8 a = 255;

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
					//Handle key presses
					else if( e.type == SDL_KEYDOWN )
					{
						//Increase alpha on w
						if( e.key.keysym.sym == SDLK_w )
						{
							//Cap if over 255
							if( a + 32 > 255 )
							{
								a = 255;
							}
							//Increment otherwise
							else
							{
								a += 32;
							}
						}
						//Decrease alpha on s
						else if( e.key.keysym.sym == SDLK_s )
						{
							//Cap if below 0
							if( a - 32 < 0 )
							{
								a = 0;
							}
							//Decrement otherwise
							else
							{
								a -= 32;
							}
						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				gBackgroundTexture.render( 0, 0 );

				//Render front blended
				gModulatedTexture.setAlpha( a );
				gModulatedTexture.render( 0, 0 );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
