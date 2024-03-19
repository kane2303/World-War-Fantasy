#ifndef TEXTURE_H
#define TEXTURE_H
#include<SDL.h>
#include<SDL_image.h>
#include<bits/stdc++.h>
using namespace std;

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile( string path );
    void free();
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};


#endif // TEXTURE_H
