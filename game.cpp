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


    const float world_width = 20.0f;
    const float world_height = 20.0f;

    m_world = new World((int) world_height * 2, (int) world_width * 2);

    m_projection_matrix = glm::ortho(-world_width, world_width, -world_height, world_height, -1.0f, 100.0f);
    m_view_matrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));
    m_world_size.left = -world_width;
    m_world_size.top = world_height;
    m_world_size.right = world_width;
    m_world_size.bottom = -world_height;

    m_snake = new Snake(glm::vec3(0.0f, 0.0f, 0.0f), 4);
    m_snake->set_world_size(-world_width, world_height, world_width, -world_height);
    m_snake->set_projection_matrix(m_projection_matrix);
    m_snake->set_view_matrix(m_view_matrix);
    m_snake->init();

    add_food();
}

Game::~Game()
{
    if (m_window)
    {
        delete m_window;
    }
    delete m_snake;

    for (std::vector<Food *>::iterator it = m_foods.begin(); it != m_foods.end(); it++)
    {
        delete *it;
    }
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
            else
            {
                handle_input(event);
            }
        }

        update(m_window->get_delta_time());

        m_window->clear_screen();
        draw();
        m_window->update();
    }
}

void Game::handle_input(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
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
                if (!m_snake->is_alive())
                {
                    m_snake->reset();
                }
            }
            break;
            case SDLK_q:
            {
                m_running = false;
            }
            break;
            case SDLK_p:
            {
                m_paused = !m_paused;
            }
            break;
        }
    }
}

void Game::update(float delta)
{
    if (m_paused)
    {
        return;
    }

    m_snake->update(delta);

    for (std::vector<Food *>::iterator it = m_foods.begin(); it != m_foods.end(); it++)
    {
        Food *food = *it;
        food->update(delta);
    }
}

void Game::draw()
{
    for (std::vector<Food *>::iterator it = m_foods.begin(); it != m_foods.end(); it++)
    {
        Food *food = *it;
        food->draw();
    }
    m_snake->draw();
}

void Game::add_food()
{
    Food *food = new Food(glm::vec3(0.0f, 0.0f, 0.0f));
    food->set_world_size(m_world_size.left, m_world_size.top, m_world_size.right, m_world_size.bottom);
    food->set_projection_matrix(m_projection_matrix);
    food->set_view_matrix(m_view_matrix);
    food->init();
    m_foods.push_back(food);
}

