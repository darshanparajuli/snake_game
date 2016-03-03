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

    Shader test_shader;
    test_shader.init("shaders/test_shader.vert", "shaders/test_shader.frag");

    glm::vec3 vertices[] = {
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f)
    };
    int indices[] = {0, 1, 2, 0, 2, 3};

    const float units = 10.0f;
    glm::mat4 projection = glm::ortho(-units, units, -units, units, -1.0f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model = glm::mat4(1.0f);

    Mesh mesh(vertices, 4, indices, 6);

    test_shader.bind();
    test_shader.set_uniform_mat4("projection", projection);
    test_shader.set_uniform_mat4("view", view);
    test_shader.unbind();

    Snake snake(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 4);
    snake.set_projection_matrix(projection);
    snake.set_view_matrix(view);
    snake.set_model_matrix(glm::mat4(1.0f));
    snake.init();

    SDL_Event event;
    float x = 0.0f;
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
        }

        window.clear_screen();

        if (!paused)
        {
            x += window.get_delta_time() * 10.0f;
            if (x > 10.0f+5/2.0f)
            {
                x = -10.0f-5/2.0f;
            }
        }

        snake.update(window.get_delta_time());
        snake.draw();

        test_shader.bind();
        test_shader.set_uniform_mat4("model", glm::scale(glm::rotate(glm::translate(model, glm::vec3(x, 0.0f, 0.0f)), 
                        360.0f * x / 1000.0f, glm::vec3(0.0f, 0.0f, 1.0f)), 
                    glm::vec3(5.0f, 5.0f, 0.0f)));
        mesh.bind();
        mesh.draw();
        mesh.unbind();
        test_shader.unbind();

        window.update();
    }

    return EXIT_SUCCESS;
}
