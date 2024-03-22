#include "Engine.h"


Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    SDL_Init( SDL_INIT_VIDEO );
    m_Window = SDL_CreateWindow( "Knight", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_SetRenderDrawColor( m_Renderer,255,255,255,255);
}
void Engine::Quit()
{
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    m_Window = NULL;
    m_Renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

void Engine::Render(){
    SDL_RenderPresent(m_Renderer);
}
