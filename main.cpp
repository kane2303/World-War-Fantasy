#include <SDL.h>
#include <SDL_image.h>
#include<bits/stdc++.h>
using namespace std;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

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

class LButton
{
public:
    LButton();

    bool handleEvent( SDL_Event* e );

    void render(string path,int x,int y,int szX,int szY);

private:
    //vi tri cua nut
    SDL_Point mPosition;

    //trang thai nut hien tai
    LButtonSprite mCurrentSprite;

    //size cua nut
    int BUTTON_WIDTH,BUTTON_HEIGHT;
};
//anh cua nut
LTexture Texturebutton;

bool init();

bool loadMedia();

void close();


SDL_Window* gWindow = NULL;


SDL_Renderer* gRenderer = NULL;


SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];


LButton StartA,StartB,StartC;
LButton NextA,NextB;

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

bool LTexture::loadFromFile( std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    mTexture = newTexture;
    return mTexture != NULL;
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

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

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

void LButton::render(string path,int x,int y,int szX,int szY)
{
    BUTTON_WIDTH = szX;
    BUTTON_HEIGHT = szY;
    Texturebutton.loadFromFile(path);
    for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
    {
        gSpriteClips[ i ].x = 0;
        gSpriteClips[ i ].y = i * 90;
        gSpriteClips[ i ].w = BUTTON_WIDTH;
        gSpriteClips[ i ].h = BUTTON_HEIGHT;
    }
    mPosition.x = x;
    mPosition.y = y;
    Texturebutton.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}

void loadImage(string path,int pX=0,int pY=0,int szX=SCREEN_WIDTH,int szY=SCREEN_HEIGHT)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    SDL_Rect renderQuad = { pX, pY, szX, szY };
    SDL_RenderCopy(gRenderer,newTexture,NULL,&renderQuad);
    SDL_DestroyTexture(newTexture);
    newTexture=NULL;
}
void Init()
{
    bool success = true;
    SDL_Init( SDL_INIT_VIDEO );
    gWindow = SDL_CreateWindow( "Knight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_SetRenderDrawColor( gRenderer,255,255,255,255);
    loadImage("assets/background.png");
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
int main( int argc, char* args[] )
{
    Init();
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
        }
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        if(trangthaitruoc == 0)
        {
            StartA.render( "assets/mainscreen/playbutton.png",500,400,350,90);
            StartB.render( "assets/mainscreen/resumebutton.png",500,500,350,90);
            StartC.render( "assets/mainscreen/quitbutton.png",500,600,350,90);
        }
        else if(trangthai == 1)
        {
            SDL_RenderClear(gRenderer);
            loadImage("assets/background.png");
            NextA.render( "assets/mainscreen/easybutton.png",500,500,350,90);
            NextB.render( "assets/mainscreen/hardbutton.png",500,600,350,90);
        }
        else if(trangthai == 2)
        {
            SDL_RenderClear(gRenderer);

        }
        SDL_RenderPresent( gRenderer );
    }
    close();

    return 0;
}
