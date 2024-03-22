#ifndef ENGINE_H
#define ENGINE_H
#include<SDL.h>
#include<SDL_image.h>

#define MAIN_WIDTH 3200
#define MAIN_HEIGHT 720

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine
{
    Engine() {}
    bool m_IsRunning;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
public:
    static Engine* GetInstance()
    {
        return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
    }
    bool Init();
    void Quit();
    void Render();

    inline bool IsRunning()
    {
        return m_IsRunning;
    }
    inline SDL_Renderer* GetRenderer()
    {
        return m_Renderer;
    }
};
#endif // ENGINE_H
