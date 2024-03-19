#ifndef BUTTON_H
#define BUTTON_H
#include<SDL.h>
#include"Texture.h"

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};
class LButton
{
public:
    LButton();
    bool handleEvent( SDL_Event* e );
    void render(LTexture* alpha,int x,int y,int szX,int szY,int layer_height);
private:
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
    int BUTTON_WIDTH,BUTTON_HEIGHT;
};

class Dot // cham di chuyen man hinh
{
public:
    static const int DOT_WIDTH = 640;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 20;
    Dot();
    void handleEvent( SDL_Event& e );
    void move();
    void render( int camX, int camY );
    int getPosX();
    int getPosY();
private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};
#endif // BUTTON_H
