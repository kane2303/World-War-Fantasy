#ifndef TEXTUREMANGE_H
#define TEXTUREMANGE_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
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
    bool loadFromFile2( string path );
    void free();
    void rendermenu( int x, int y, SDL_Rect* clip = NULL, bool flip=false);
    void render( int x, int y, SDL_Rect* clip = NULL, bool flip=false, bool hero=false);
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
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
