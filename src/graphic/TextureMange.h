#ifndef TEXTUREMANGE_H
#define TEXTUREMANGE_H
#include<SDL.h>
#include<SDL_image.h>
#include<bits/stdc++.h>
#include"Engine.h"
#define gRenderer  Engine::GetInstance()->GetRenderer()
using namespace std;


class LTexture
{
public:

    int xx=0;
    LTexture();
    ~LTexture();
    bool loadFromFile( string path );
    void free();
    void render( int x, int y, SDL_Rect* clip = NULL, bool flip=false);
    int getWidth();
    int getHeight();
    void SetRender();
    void SetTexture();
    void setAlpha( Uint8 alpha );
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif // TEXTUREMANGE_H
