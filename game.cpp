#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "game.h"

Game::Game()
{
    m_window = new GameWindow("Snake", 600, 600);
    if (!m_window->init())
    {
        std::cerr << "Failed to init GameWindow" << std::endl;
        m_running = false;
    }
    else
    {
        m_running = true;
    }
    m_paused = false;

    const float units = 15.0f;
    glm::mat4 projection = glm::ortho(-units, units, -units, units, -1.0f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    m_snake = new Snake(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 12);
    m_snake->set_projection_matrix(projection, units);
    m_snake->set_view_matrix(view);
    m_snake->init();
}

Game::~Game()
{
    if (m_window)
    {
        delete m_window;
    }
    delete m_snake;
}

void Game::run()
{
    SDL_Event event;
    while (m_running && m_window->is_running())
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_window->exit();
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        m_window->resize(event.window.data1, event.window.data2);
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    {
                        m_paused = false;
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        m_paused = true;
                    }
                    break;
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        m_snake->set_move_direction(Snake::NORTH);
                    }
                    break;
                    case SDLK_DOWN:
                    {
                        m_snake->set_move_direction(Snake::SOUTH);
                    }
                    break;
                    case SDLK_LEFT:
                    {
                        m_snake->set_move_direction(Snake::WEST);
                    }
                    break;
                    case SDLK_RIGHT:
                    {
                        m_snake->set_move_direction(Snake::EAST);
                    }
                    break;
                    case SDLK_r:
                    {
                        m_snake->reset();
                    }
                    break;
                    case SDLK_q:
                    {
                        m_running = false;
                    }
                    break;
                }
            }
        }

        m_window->clear_screen();

        if (!m_paused)
        {
            m_snake->update(m_window->get_delta_time());
        }

        m_snake->draw();

        m_window->update();
    }
}
