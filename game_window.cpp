#include "game_window.h"
#include <iostream>

GameWindow::GameWindow(const char *title, int width, int height)
    : m_title(title), m_width(width), m_height(height)
{
    m_running = true;
    m_window = NULL;
    m_gl_context = NULL;
    m_prev_frame_time = 0;
    m_frame_count = 0;
    m_prev_time = 0;
    m_delta_time = 0.0f;
}

GameWindow::~GameWindow()
{
    if (m_window)
    {
        SDL_GL_DeleteContext(m_gl_context);
        SDL_DestroyWindow(m_window);
    }

    SDL_Quit();
}

bool GameWindow::init_opengl()
{
    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        // TODO(darshan): check for supported GL version
        return false;
    }

    glViewport(0, 0, m_width, m_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return true;
}

bool GameWindow::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, m_width, m_height,
                                SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    if (m_window == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    m_gl_context = SDL_GL_CreateContext(m_window);

    if (m_gl_context == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (init_opengl())
    {
        char *version = (char *) glGetString(GL_VERSION);
        char *version_glsl = (char *) glGetString(GL_SHADING_LANGUAGE_VERSION);
        std::cout << "OpenGL version: " << version << std::endl;
        std::cout << "GLSL version: " << version_glsl << std::endl;
    }
    else
    {
        return false;
    }

    m_prev_time = SDL_GetTicks();

    return true;
}

void GameWindow::update()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "Error: " << gluErrorString(error) << std::endl;
    }

    SDL_GL_SwapWindow(m_window);

    unsigned int time = SDL_GetTicks();

    m_delta_time = (time - m_prev_time) / (1000.0f);
    m_prev_time = time;

    unsigned int diff = time - m_prev_frame_time;
    if (diff >= 1000)
    {
        // std::cout << "fps: " << m_frame_count << std::endl;
        m_prev_frame_time = time;
        m_frame_count = 0;
    }
    else
    {
        m_frame_count++;
    }
}

void GameWindow::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    SDL_SetWindowSize(m_window, width, height);
    glViewport(0, 0, m_width, m_height);
}
