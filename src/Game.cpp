#include <iostream>
#include "Game.h"

Game::Game(const std::string &title, uint32_t width, uint32_t height,
        uint32_t framesPerSecond)
: m_title(title),
  m_width(width),
  m_height(height),
  m_window(NULL),
  m_state(GS_RUNNING),
  m_framesPerSecond(framesPerSecond),
  m_timePerFrame(1000 / framesPerSecond) // milliseconds
{

}

Game::~Game()
{

}

bool Game::Init()
{
    //
    // INITIALIZE SDL
    //
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "ERROR: Initializing SDL." << '\n';
        return false;
    }

    //
    // GL CONTEXT ATTRIBUTES
    //
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //
    // CREATING WINDOW
    //
    m_window = SDL_CreateWindow(
        m_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_width,
        m_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if(m_window == NULL)
    {
        std::cerr << "ERROR: Creating the SDL Window." << '\n';
        return false;
    }

    //
    // CREATING GL CONTEXT
    //
    m_glContext = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_glContext);

    //  0 - for immediate updates,
    //  1 - for updates synchronized with the vertical retrace,
    // -1 - for late swap tearing
    SDL_GL_SetSwapInterval(1);

    //
    // GL ORTHOGRAPHIC PROJECTION
    //
    float left = 0;
    float right = static_cast<float>(m_width);
    float bottom = static_cast<float>(m_height);
    float top = 0;

    glViewport(0, 0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1.0, 1.0);
    glMatrixMode( GL_MODELVIEW );
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //
    // GL TEXTURE
    //
    glEnable(GL_TEXTURE_2D);

    //
    // GL BLEND
    //
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_ALPHA_TEST);

    //
    // INITIALIZE DEVIL AND DEVILU
    //
    ilInit();
    iluInit();
    ilClearColour(0, 0, 0, 0);

    ILenum ilError = ilGetError();
    if(ilError != IL_NO_ERROR)
    {
        printf("Error initializing DevIL! %s\n", iluErrorString(ilError));
        return false;
    }

    OnInit();

    return true;
}

void Game::OnInit()
{
    // override
}

void Game::Render()
{
    // FIXME: (Pavel) Clear color should be a setting
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    OnRender();

    SDL_GL_SwapWindow(m_window);
}

void Game::Update()
{
    OnUpdate();
}

bool Game::Run()
{
    if(!Init())
    {
        std::cerr << "ERROR: Initializing the Game." << '\n';
        return false;
    }

    SDL_Event event;

    while(m_state == GS_RUNNING)
    {
        Uint32 start = SDL_GetTicks();

        HandleEvent(event);
        Update();
        Render();

        Uint32 elapsedTime = SDL_GetTicks() - start;
        if(m_timePerFrame > elapsedTime)
        {
            SDL_Delay(m_timePerFrame - elapsedTime);
        }
    }

    Cleanup();
    return true;
}

void Game::HandleEvent(SDL_Event &event)
{
    //
    // EVENTS
    //
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Exit();
                break;
            case SDL_KEYDOWN:
                OnKeyDown(event.key);
                break;
            case SDL_KEYUP:
                OnKeyUp(event.key);
                break;
            case SDL_MOUSEMOTION:
                OnMouseMotion(event.motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                OnMouseButtonDown(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                OnMouseButtonUp(event.button);
                break;
        }
    }
}

void Game::Cleanup()
{
    OnCleanup();

    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::OnCleanup()
{
    // override
}

void Game::OnKeyDown(SDL_KeyboardEvent& event)
{
    /*
    typedef struct SDL_KeyboardEvent
    {
        Uint32 type;        // < ::SDL_KEYDOWN or ::SDL_KEYUP
        Uint32 timestamp;
        Uint32 windowID;    // < The window with keyboard focus, if any
        Uint8 state;        // < ::SDL_PRESSED or ::SDL_RELEASED
        Uint8 repeat;       // < Non-zero if this is a key repeat
        Uint8 padding2;
        Uint8 padding3;
        SDL_Keysym keysym;  // < The key that was pressed or released
    } SDL_KeyboardEvent;
    */

    // override
}

void Game::OnKeyUp(SDL_KeyboardEvent& event)
{
    /*
    typedef struct SDL_KeyboardEvent
    {
        Uint32 type;        // < ::SDL_KEYDOWN or ::SDL_KEYUP
        Uint32 timestamp;
        Uint32 windowID;    // < The window with keyboard focus, if any
        Uint8 state;        // < ::SDL_PRESSED or ::SDL_RELEASED
        Uint8 repeat;       // < Non-zero if this is a key repeat
        Uint8 padding2;
        Uint8 padding3;
        SDL_Keysym keysym;  // < The key that was pressed or released
    } SDL_KeyboardEvent;
    */

    // override
}

void Game::OnResize(uint32_t width, uint32_t height)
{
    // override
}

void Game::Exit()
{
    OnExit();

    m_state = GS_QUIT;
}

void Game::OnExit()
{
    // override
}

void Game::OnUpdate()
{
    // override
}

void Game::OnRender()
{
    // override
}

void Game::OnMouseButtonDown(SDL_MouseButtonEvent& event)
{
    /*
    typedef struct SDL_MouseButtonEvent
    {
        Uint32 type;        // < ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP
        Uint32 timestamp;
        Uint32 windowID;    // < The window with mouse focus, if any
        Uint32 which;       // < The mouse instance id, or SDL_TOUCH_MOUSEID
        Uint8 button;       // < The mouse button index
        Uint8 state;        // < ::SDL_PRESSED or ::SDL_RELEASED
        Uint8 clicks;       // < 1 for single-click, 2 for double-click, etc.
        Uint8 padding1;
        Sint32 x;           // < X coordinate, relative to window
        Sint32 y;           // < Y coordinate, relative to window
    } SDL_MouseButtonEvent;
    */

    // override
}


void Game::OnMouseButtonUp(SDL_MouseButtonEvent &event)
{
    /*
    typedef struct SDL_MouseButtonEvent
    {
        Uint32 type;        // < ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP
        Uint32 timestamp;
        Uint32 windowID;    // < The window with mouse focus, if any
        Uint32 which;       // < The mouse instance id, or SDL_TOUCH_MOUSEID
        Uint8 button;       // < The mouse button index
        Uint8 state;        // < ::SDL_PRESSED or ::SDL_RELEASED
        Uint8 clicks;       // < 1 for single-click, 2 for double-click, etc.
        Uint8 padding1;
        Sint32 x;           // < X coordinate, relative to window
        Sint32 y;           // < Y coordinate, relative to window
    } SDL_MouseButtonEvent;
    */

    // override
}

void Game::OnMouseMotion(SDL_MouseMotionEvent& event)
{
    /*
    typedef struct SDL_MouseMotionEvent
    {
        Uint32 type;
        Uint32 timestamp;
        Uint32 windowID;    // The window with mouse focus, if any
        Uint32 which;       // The mouse instance id, or SDL_TOUCH_MOUSEID
        Uint32 state;       // The current button state
        Sint32 x;           // X coordinate, relative to window
        Sint32 y;           // Y coordinate, relative to window
        Sint32 xrel;        // The relative motion in the X direction
        Sint32 yrel;        // The relative motion in the Y direction
    } SDL_MouseMotionEvent;
    */

    // override
}
