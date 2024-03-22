#include "Button.h"

SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];


LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
    BUTTON_WIDTH = 0;
    BUTTON_HEIGHT = 0;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}


bool LButton::handleEvent( SDL_Event* e )
{
    bool flag=0;
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        int x, y;
        SDL_GetMouseState( &x, &y );

        bool inside = ( x >= mPosition.x && x <= mPosition.x + BUTTON_WIDTH && y >= mPosition.y && y <= mPosition.y + BUTTON_HEIGHT);

        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch( e->type )
            {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                flag=1;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
    return flag;
}

void LButton::render(LTexture* Alpha,int x,int y,int szX,int szY,int layer_height)
{
    BUTTON_WIDTH = szX;
    BUTTON_HEIGHT = szY;
    for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
    {
        gSpriteClips[ i ].x = 0;
        gSpriteClips[ i ].y = i * layer_height;
        gSpriteClips[ i ].w = BUTTON_WIDTH;
        gSpriteClips[ i ].h = BUTTON_HEIGHT;
    }
    mPosition.x = x;
    mPosition.y = y;
    Alpha->render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}


Dot::Dot()
{
    mPosX = 0;
    mPosY = 700;
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            mVelX -= DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += DOT_VEL;
            break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            mVelX += DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= DOT_VEL;
            break;
        }
    }
}


int Dot::getPosX()
{
    return mPosX;
}

int Dot::getPosY()
{
    return mPosY;
}

void Dot::move()
{
    mPosX += mVelX;

    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > 3200 ) )
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > 720 ) )
    {
        mPosY -= mVelY;
    }
}

