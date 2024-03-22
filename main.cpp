#include <SDL.h>
#include <SDL_image.h>
#include<bits/stdc++.h>
#include"Button.h"
#include"TextureMange.h"
#include"Engine.h"
#include"Troops.h"
#define gRenderer  Engine::GetInstance()->GetRenderer()
using namespace std;


SDL_Rect base;
//anh cua nut
LTexture Texturebutton;
//bg
LTexture Texturebackground1,Texturebackground2;
//Texture cua vat
LTexture gBootcamp,gBootcamp2,BG2,BG3,BGframe;

LTexture TextChange;

void loadMedia();

LButton StartA,StartB,StartC;
LTexture TextStA,TextStB,TextStC;

LButton NextA,NextB;
LTexture TextNxtA,TextNxtB;

LButton TroopsIcon1,TroopsIcon2,TroopsIcon3;
LTexture TextTroopsIcon1,TextTroopsIcon2,TextTroopsIcon3;

int trangthai=0;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

Dot dot;
void loadMedia()
{
    Texturebackground2.SetTexture();
    Texturebackground1.loadFromFile("assets/background.jpg");
    TextStA.loadFromFile("assets/mainscreen/playbutton.png");
    TextStB.loadFromFile("assets/mainscreen/resumebutton.png");
    TextStC.loadFromFile("assets/mainscreen/quitbutton.png");

    TextNxtA.loadFromFile("assets/mainscreen/easybutton.png");
    TextNxtB.loadFromFile("assets/mainscreen/hardbutton.png");

    BG2.loadFromFile("assets/bg.png");
    base = {0,680,SCREEN_WIDTH,40};
    gBootcamp.loadFromFile("assets/castle.png");
    gBootcamp2.loadFromFile("assets/castle.png");
    BGframe.loadFromFile("assets/BGframe.png");
    TextTroopsIcon1.loadFromFile("assets/troopsicon1.png");
    TextTroopsIcon2.loadFromFile("assets/troopsicon2.png");
    TextTroopsIcon3.loadFromFile("assets/troopsicon3.png");
    TextChange.loadFromFile("assets/chuyencanh.png");

    BG3.loadFromFile("assets/background2.jpg");
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
}
/**                                                                              start merge                                      **/
/**                                                                              start merge                                      **/
/**                                                                              start merge                                      **/

/**                                                                              end merge                                      **/
/**                                                                              end merge                                      **/
/**                                                                              end merge                                      **/
int dengiolendoi=0,alpha=0;
int main(int argc,char** argv )
{
    Engine::GetInstance()->Init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        int trangthaitruoc = trangthai;
        int calling=0;
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
//                dot.handleEvent(e);
//                if(TroopsIcon1.handleEvent(&e)) calling = 1;
//                if(TroopsIcon2.handleEvent(&e)) calling = 2;
//                if(TroopsIcon3.handleEvent(&e)) calling = 3;
            }
        }
//        SDL_SetRenderDrawColor( gRenderer, 54, 104, 168, 255 );
        if(trangthaitruoc == 0)
        {
            Texturebackground1.render(0,0);
            StartA.render( &TextStA,490,200,375,90,90);
            StartB.render( &TextStB,490,300,375,90,90);
            StartC.render( &TextStC,490,400,375,90,90);
        }
        if(trangthai == 1)
        {
            Texturebackground1.render(0,0);
            NextA.render( &TextNxtA,490,200,375,90,90);
            NextB.render( &TextNxtB,490,300,375,90,90);
        }
        if(trangthai == 2)
        {
            SDL_RenderClear(gRenderer);
            Run_dot();
            Texturebackground2.SetRender();
            SDL_RenderClear(gRenderer);
            //mat trong

            BG2.render(0,0);
            gBootcamp.render(5,480);
            SDL_Rect tmp{0,0,200,200};
            gBootcamp2.render(MAIN_WIDTH-205,480,&tmp,1);


            SDL_SetRenderTarget(gRenderer,nullptr);
            SDL_RenderClear(gRenderer);
            Texturebackground2.render(0,0,&camera);
            // chay theo cam
            SDL_SetRenderDrawColor( gRenderer, 54, 104, 168, 255 );
            SDL_RenderFillRect(gRenderer,&base);
            BGframe.render(970,0);
            TroopsIcon1.render( &TextTroopsIcon1,1018,32,54,54,54);
            TroopsIcon2.render( &TextTroopsIcon2,1098,32,54,54,54);
            TroopsIcon3.render( &TextTroopsIcon3,1178,32,54,54,54);
            dengiolendoi++;

            if(dengiolendoi>=50)
            {
                if(alpha==254) {
                    alpha=255;
                    trangthai=3;
                }
                else alpha++;
                TextChange.setAlpha(alpha);
                TextChange.render(0,0);
            }

        }
        if(trangthai==3)
        {
            BG3.render(0,0);
        }
        Engine::GetInstance()->Render();
        SDL_RenderClear(gRenderer);
        if(trangthai!=trangthaitruoc)
        {
            if(trangthai==1)
            {
                TextStA.free();
                TextStB.free();
                TextStC.free();
            }
            else if(trangthai==2)
            {
                Texturebackground1.free();
                TextNxtA.free();
                TextNxtB.free();
            }
        }
    }
    Engine::GetInstance()->Quit();

    return 0;
}
