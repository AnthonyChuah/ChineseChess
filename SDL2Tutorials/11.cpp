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
  void render( int x, int y, SDL_Rect* clip = NULL );
  int getWidth();
  int getHeight();
private:
  SDL_Texture* mTexture;
  int mWidth;
  int mHeight;
};

bool init();
bool loadMedia();
void close();
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gSpriteClips[ 4 ];
LTexture gSpriteSheetTexture;

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
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == NULL ) {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    } else {
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }
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

// I have a texture, and I want to render a clip of the texture only.
void LTexture::render( int x, int y, SDL_Rect* clip ) {
  // clip is an SDL_Rect, which "clips" a rectangle out of the mTexture according to x and y.
  //Set rendering space and render to screen
  // So clip is SDL_Rect { x_pos, y_pos, width, height } RELATIVE to the texture image.
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
  //Set clip rendering dimensions
  if( clip != NULL ) {
    // If there is a clip, you reduce width and height to match the clip's w and h.
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  // Render to screen, RELATIVE to the screen. clip "grabs" the sub-image, renderQuad specifies
  // the rendering position on the SCREEN!
  // 3rd arg, clip, is the "source rectangle". It defines what PART of the texture you want to
  // render. If this is NULL, the whole texture is rendered.
  SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth() {
  return mWidth;
}

int LTexture::getHeight() {
  return mHeight;
}

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
	  printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
	  success = false;
	}
      }
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  if( !gSpriteSheetTexture.loadFromFile( "11_cliprender/dots.png" ) ) {
    printf( "Failed to load sprite sheet texture!\n" );
    success = false;
  } else {
    //Set top left sprite
    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w = 100;
    gSpriteClips[ 0 ].h = 100;
    //Set top right sprite
    gSpriteClips[ 1 ].x = 100;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w = 100;
    gSpriteClips[ 1 ].h = 100;
    //Set bottom left sprite
    gSpriteClips[ 2 ].x =   0;
    gSpriteClips[ 2 ].y = 100;
    gSpriteClips[ 2 ].w = 100;
    gSpriteClips[ 2 ].h = 100;
    //Set bottom right sprite
    gSpriteClips[ 3 ].x = 100;
    gSpriteClips[ 3 ].y = 100;
    gSpriteClips[ 3 ].w = 100;
    gSpriteClips[ 3 ].h = 100;
  }
  return success;
}

void close() {
  gSpriteSheetTexture.free();
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

int main( int argc, char* args[] ) {
  if( !init() ) {
    printf( "Failed to initialize!\n" );
  } else {
    if( !loadMedia() ) {
      printf( "Failed to load media!\n" );
    } else {
      bool quit = false;
      SDL_Event e;
      while( !quit ) {
	while( SDL_PollEvent( &e ) != 0 ) {
	  if( e.type == SDL_QUIT ) {
	    quit = true;
	  }
	}
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
	//Render top left sprite
	gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ] );
	//Render top right sprite
	gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );
	//Render bottom left sprite
	gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );
	//Render bottom right sprite
	gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );
	SDL_RenderPresent( gRenderer );
      }
    }
  }
  close();
  return 0;
}
