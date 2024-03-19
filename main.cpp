#include <SDL.h>
#include <SDL_image.h>
#include<bits/stdc++.h>
#include"Button.h"
#include"Texture.h"
using namespace std;
const int MAIN_WIDTH = 3200;
const int MAIN_HEIGHT = 720;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TOTAL_BUTTONS = 4;


SDL_Rect base;
//anh cua nut
LTexture Texturebutton;
//bg
LTexture Texturebackground1,Texturebackground2;
//texture cua dot
LTexture gDotTexture;
//Texture cua vat
LTexture gBootcamp;

bool init();

void loadMedia();

void close();


SDL_Window* gWindow = NULL;


SDL_Renderer* gRenderer = NULL;


LButton StartA,StartB,StartC;
LTexture TextStA,TextStB,TextStC;

LButton NextA,NextB;
LTexture TextNxtA,TextNxtB;


bool LTexture::loadFromFile( std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );

    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void Init()
{
    bool success = true;
    SDL_Init( SDL_INIT_VIDEO );
    gWindow = SDL_CreateWindow( "Knight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
}
void loadMedia()
{
    Texturebackground1.loadFromFile("assets/background.jpg");
    TextStA.loadFromFile("assets/mainscreen/playbutton.png");
    TextStB.loadFromFile("assets/mainscreen/resumebutton.png");
    TextStC.loadFromFile("assets/mainscreen/quitbutton.png");

    TextNxtA.loadFromFile("assets/mainscreen/easybutton.png");
    TextNxtB.loadFromFile("assets/mainscreen/hardbutton.png");

    Texturebackground2.loadFromFile("assets/bg.png");
    base = {0,680,SCREEN_WIDTH,40};
    gDotTexture.loadFromFile("assets/dot.png");
    gBootcamp.loadFromFile("assets/castle.png");
}

void close()
{
    Texturebutton.free();

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int trangthai=0;
Dot dot;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

void Dot::move()
{
    mPosX += mVelX;

    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > MAIN_WIDTH ) )
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > MAIN_HEIGHT ) )
    {
        mPosY -= mVelY;
    }
}

void Dot::render( int camX, int camY )
{
    gDotTexture.render( mPosX - camX, mPosY - camY );
}
void Run_dot()
{
    dot.move();
    camera.x = ( dot.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
    if( camera.x < 0 ) camera.x = 0;
    if( camera.y < 0 ) camera.y = 0;
    if( camera.x > MAIN_WIDTH - camera.w ) camera.x = MAIN_WIDTH - camera.w;
    if( camera.y > MAIN_HEIGHT - camera.h ) camera.y = MAIN_HEIGHT - camera.h;
    Texturebackground2.render( 0, 0, &camera );
    dot.render( camera.x, camera.y );
}

int main( int argc, char* args[] )
{
    Init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        int trangthaitruoc = trangthai;
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            if(trangthai==0)
            {
                if(StartA.handleEvent(&e)) trangthai = 1;
                StartB.handleEvent(&e);
                if(StartC.handleEvent(&e)) quit = 1;
            }
            else if( trangthai == 1 )
            {
                if( NextA.handleEvent(&e) || NextB.handleEvent(&e) )
                {
                    trangthai = 2;
                }
            }
            else if( trangthai == 2 )
            {
                dot.handleEvent(e);
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 54, 104, 168, 255 );
        if(trangthaitruoc == 0)
        {
            Texturebackground1.render(0,0);
            StartA.render( &TextStA,490,200,375,90,90);
            StartB.render( &TextStB,490,300,375,90,90);
            StartC.render( &TextStC,490,400,375,90,90);
        }
        else if(trangthai == 1)
        {
            Texturebackground1.render(0,0);
            NextA.render( &TextNxtA,490,200,375,90,90);
            NextB.render( &TextNxtB,490,300,375,90,90);
        }
        else if(trangthai == 2)
        {
            Run_dot();
            SDL_RenderFillRect(gRenderer,&base);
            gBootcamp.render(5,480);

        }
        SDL_RenderPresent( gRenderer );
        SDL_RenderClear(gRenderer);

        if(trangthai!=trangthaitruoc)
        {
            if(trangthai==1) {
                TextStA.free();
                TextStB.free();
                TextStC.free();
            }
            else if(trangthai==2){
                Texturebackground1.free();
                TextNxtA.free();
                TextNxtB.free();
            }
        }
    }
    close();

    return 0;
}
