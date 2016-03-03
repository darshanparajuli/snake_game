#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include "game_window.h"
#include "mesh.h"
#include "shader.h"
#include "snake.h"

int main()
{
    GameWindow window("Snake", 600, 600);
    if (!window.init())
    {
        std::cerr << "window init failed" << std::endl;
        return EXIT_FAILURE;
    }

    const float units = 15.0f;
    glm::mat4 projection = glm::ortho(-units, units, -units, units, -1.0f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    Snake snake(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 4);
    snake.set_projection_matrix(projection, units);
    snake.set_view_matrix(view);
    snake.set_model_matrix(glm::mat4(1.0f));
    snake.init();

    SDL_Event event;
    bool paused = false;
    while (window.is_running())
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                window.exit();
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    {
                        window.resize(event.window.data1, event.window.data2);
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                    {
                        paused = false;
                    }
                    break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                    {
                        paused = true;
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
                        snake.set_move_direction(Snake::NORTH);
                    }
                    break;
                    case SDLK_DOWN:
                    {
                        snake.set_move_direction(Snake::SOUTH);
                    }
                    break;
                    case SDLK_LEFT:
                    {
                        snake.set_move_direction(Snake::WEST);
                    }
                    break;
                    case SDLK_RIGHT:
                    {
                        snake.set_move_direction(Snake::EAST);
                    }
                    break;
                }
            }
        }

        window.clear_screen();

        if (!paused)
        {
            snake.update(window.get_delta_time());
        }

        snake.draw();

        window.update();
    }

    return EXIT_SUCCESS;
}
