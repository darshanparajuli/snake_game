#include "game.h"
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

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
    m_initial_pause = true;

    const int world_width = 40;
    const int world_height = 40;

    m_world = new World(world_height + 1, world_width + 1);
    m_world_size.left = -world_width / 2.0f;
    m_world_size.top = world_height / 2.0f;
    m_world_size.right = world_width / 2.0f;
    m_world_size.bottom = -world_height / 2.0f;

    m_projection_matrix =
        glm::ortho(m_world_size.left, m_world_size.right, m_world_size.bottom, m_world_size.top, -1.0f, 100.0f);
    m_view_matrix =
        glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    m_snake = new Snake(m_world, glm::vec3(0.0f, 0.0f, 0.0f), 4);
    m_snake->set_world_size(m_world_size);
    m_snake->set_projection_matrix(m_projection_matrix);
    m_snake->set_view_matrix(m_view_matrix);
    m_snake->init();

    m_food = new Food(m_world);
    m_food->set_world_size(m_world_size);
    m_food->set_projection_matrix(m_projection_matrix);
    m_food->set_view_matrix(m_view_matrix);
    m_food->init();

    m_background = new Background(m_world);
    m_background->set_world_size(m_world_size);
    m_background->set_projection_matrix(m_projection_matrix);
    m_background->set_view_matrix(m_view_matrix);
    m_background->init();

    std::srand(time(NULL));
}

Game::~Game()
{
    if (m_window)
    {
        delete m_window;
    }
    delete m_snake;
    delete m_food;
    delete m_background;
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
                m_initial_pause = false;
            }
            break;
            case SDLK_DOWN:
            {
                m_snake->set_move_direction(Snake::SOUTH);
                m_initial_pause = false;
            }
            break;
            case SDLK_LEFT:
            {
                m_snake->set_move_direction(Snake::WEST);
                m_initial_pause = false;
            }
            break;
            case SDLK_RIGHT:
            {
                m_snake->set_move_direction(Snake::EAST);
                m_initial_pause = false;
            }
            break;
            case SDLK_r:
            {
                if (!m_snake->is_alive())
                {
                    reset();
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
    if (!m_paused && !m_initial_pause)
    {
        m_snake->update(delta);
    }

    m_food->update(delta);
    if (m_food->is_eaten())
    {
        if (!m_food->place_food())
        {
            // win
        }
    }

    m_background->set_snake_position(m_snake->get_head_position());
    m_background->set_food_position(m_food->get_transform()->position);
    m_background->update(delta);

    // for debugging
    // m_world->print();
}

void Game::draw()
{
    m_background->draw();
    m_food->draw();
    m_snake->draw();
}

void Game::reset()
{
    m_world->reset();
    m_snake->reset();
    m_initial_pause = true;
    m_food->place_food();
}
