#include <iostream>
#include "LOpenGL.h"
#include "LDevIL.h"
#include "World.h"
#include "BitmapFont.h"

// constants
const int SCREEN_WIDTH = 1136;
const int SCREEN_HEIGHT = 640;
const int SCREEN_FPS = 60;
const char* SCREEN_TITLE = "Asteroids";

// methods
bool InitializeGL();
bool LoadingMedia();
void Render();
void Update();
void OnKeyDownEvent(unsigned char key, int x, int y);
void OnKeyUpEvent(unsigned char key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void GameLoop(int value);

asteroids::World* g_world = nullptr;

bool InitializeGL()
{
    glViewport(0.f, 0.f, g_world->GetWidth(), g_world->GetHeight());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(g_world->GetLeft(), g_world->GetRight(),
            g_world->GetBottom(), g_world->GetTop(), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_TEXTURE_2D);

    GLenum error = glGetError();
    if (error !=  GL_NO_ERROR )
    {
        std::cout << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;
        return false;
    }

    // initialize DevIL and DevILU
    ilInit();
    iluInit();
    ilClearColour(0, 0, 0, 0);

    // check for errors
    ILenum ilError = ilGetError();
    if(ilError != IL_NO_ERROR)
    {
        printf( "Error initializing DevIL! %s\n", iluErrorString( ilError ) );
        return false;
    }

    return true;
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    g_world->Render();

    glutSwapBuffers();
}

void Update()
{
    g_world->Update();
}

void OnKeyDownEvent(unsigned char key, int x, int y)
{
    g_world->OnKeyDown(key);
}

void OnKeyUpEvent(unsigned char key, int x, int y)
{
    g_world->OnKeyUp(key);
}

void OnMouseMoveEvent(int x, int y)
{
    g_world->OnMouseMove(x, y);
}

void OnMouseClick(int button, int state, int x, int y)
{
    g_world->OnMouseClick(button, state, x, y);
}

void GameLoop(int value)
{
    Update();
    Render();
    glutTimerFunc( 1000 / SCREEN_FPS, GameLoop, value);
}

int main(int argc, char** argv)
{
    g_world = new asteroids::World(SCREEN_WIDTH, SCREEN_HEIGHT);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow(SCREEN_TITLE);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
            GLUT_ACTION_CONTINUE_EXECUTION);

    if(!InitializeGL())
    {
        std::cout << "Unable to initalize OpenGL." << std::endl;
    }

    if(!g_world->LoadResources())
    {
        // TODO: (Pavel) Clean up the world and end
        std::cout << "Unable to load the game resources." << std::endl;
    }

    glutDisplayFunc(Render);
    glutKeyboardFunc(OnKeyDownEvent);
    glutKeyboardUpFunc(OnKeyUpEvent);
    glutPassiveMotionFunc(OnMouseMoveEvent);
    glutMouseFunc(OnMouseClick);
    glutTimerFunc(1000 / SCREEN_FPS, GameLoop, 0);
    glutMainLoop();

    if(g_world != nullptr)
    {
        delete g_world;
        g_world = nullptr;
    }

    return 0;
}
