#include "AsteroidGame.h"

namespace asteroids
{
    AsteroidGame::AsteroidGame(const std::string &title, uint32_t width, uint32_t height,
            uint32_t framesPerSecond)
    : Game(title, width, height, framesPerSecond),
      m_world(new World(width, height))
    {

    }

    AsteroidGame::~AsteroidGame()
    {
        if(m_world != nullptr)
        {
            delete m_world;
            m_world = nullptr;
        }
    }

    void AsteroidGame::OnKeyDown(SDL_KeyboardEvent &event)
    {
        switch(event.keysym.sym)
        {
            case SDLK_w:
                m_world->OnKeyDown('w');
                break;
            case SDLK_s:
                m_world->OnKeyDown('s');
                break;
            case SDLK_a:
                m_world->OnKeyDown('a');
                break;
            case SDLK_d:
                m_world->OnKeyDown('d');
                break;
            case SDLK_SPACE:
                m_world->OnKeyDown(' ');
                break;
            case SDLK_ESCAPE:
                Exit();
                break;
        }
    }

    void AsteroidGame::OnKeyUp(SDL_KeyboardEvent &event)
    {
        switch(event.keysym.sym)
        {
            case SDLK_w:
                m_world->OnKeyUp('w');
                break;
            case SDLK_s:
                m_world->OnKeyUp('s');
                break;
            case SDLK_a:
                m_world->OnKeyUp('a');
                break;
            case SDLK_d:
                m_world->OnKeyUp('d');
                break;
            case SDLK_SPACE:
                m_world->OnKeyUp(' ');
                break;
        }
    }

    void AsteroidGame::OnMouseButtonDown(SDL_MouseButtonEvent &event)
    {
        m_world->OnMouseClick(event.button, event.state, event.x, event.y);
    }

    void AsteroidGame::OnMouseButtonUp(SDL_MouseButtonEvent &event)
    {
        // do nothing
    }

    void AsteroidGame::OnUpdate()
    {
        m_world->Update();
    }

    void AsteroidGame::OnRender()
    {
        m_world->Render();
    }

    void AsteroidGame::OnInit()
    {
        if(!m_world->LoadResources())
        {
            std::cerr << "ERROR: Unable to load the game resources." << '\n';
        }
    }
}