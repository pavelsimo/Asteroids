#ifndef __GAME_H_
#define __GAME_H_

#include <string>

#include <SDL.h>
#undef main
#include <SDL_opengl.h>
#include "LDevIL.h"

enum GameState
{
    GS_RUNNING = 0,
    GS_PAUSED  = 1,
    GS_QUIT    = 2
};

class Game
{
    public:
        //
        // ctor & dtor
        //
        Game(const std::string& title, uint32_t width, uint32_t height,
                uint32_t framesPerSecond = 60);
        virtual ~Game();

        bool Run();

        virtual void OnCleanup();
        virtual void OnInit();
        virtual void OnKeyDown(SDL_KeyboardEvent& event);
        virtual void OnKeyUp(SDL_KeyboardEvent& event);
        virtual void OnMouseButtonDown(SDL_MouseButtonEvent& event);
        virtual void OnMouseButtonUp(SDL_MouseButtonEvent& event);
        virtual void OnMouseMotion(SDL_MouseMotionEvent &event);
        virtual void OnResize(uint32_t width, uint32_t height);
        virtual void OnExit();
        virtual void OnUpdate();
        virtual void OnRender();

    private:
        void Render();
        void Update();
        void Exit();
        bool Init();
        void HandleEvent(SDL_Event& event);
        void Cleanup();

    protected:
        GameState m_state;
        std::string m_title;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_framesPerSecond;
        uint32_t m_timePerFrame;
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
};

#endif //__GAME_H_
