#include "TextureMange.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}



bool LTexture::loadFromFile( string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromFile2( string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 255, 255, 255 ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::rendermenu( int x, int y, SDL_Rect* clip, bool flip){
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	if(!flip) SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
	else {
	    SDL_RendererFlip flipType= SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0.0, nullptr, flipType);
	}
}
void LTexture::render( int x, int y, SDL_Rect* clip, bool flip, bool hero){
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

    if(hero) renderQuad.y= 720 - renderQuad.h;
    else renderQuad.y= 700 - renderQuad.h;

	if(!flip) SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
	else {
	    SDL_RendererFlip flipType= SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0.0, nullptr, flipType);
	}
}


void LTexture::SetTexture()
{
    mTexture = SDL_CreateTexture(
            gRenderer,SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, MAIN_WIDTH,MAIN_HEIGHT
    );
}

void LTexture::SetRender()
{
    SDL_SetRenderTarget(gRenderer,mTexture);
}

void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
