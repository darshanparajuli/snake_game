#include <iostream>
#include "snake.h"
#include <glm/gtc/matrix_transform.hpp>

Snake::Snake(const glm::vec3 &init_pos, float size, int body_count)
{
    m_size = (size <= 0) ? 1 : size;
    m_delta_size = 0.0f;
    m_pause_movement = false;
    m_dir = NORTH;

    for (int i = 0; i < body_count; i++)
    {
        snake_body *body = new snake_body;
        body->position = init_pos - glm::vec3(0.0f, m_size * i, 0.0f);
        body->scale_factor = glm::vec2(0.8f, 0.8f);
        m_body.push_back(body);
    }

    glm::vec3 vertices[] = {
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f)
    };
    int indices[] = {0, 1, 2, 0, 2, 3};

    m_mesh = new Mesh(vertices, 4, indices, 6);

    m_shader = new Shader();
    m_shader->init("shaders/snake.vert", "shaders/snake.frag");
}

Snake::~Snake()
{
    for (std::deque<snake_body *>::iterator it = m_body.begin(); it != m_body.end(); it++)
    {
        if (*it)
        {
            delete *it;
        }
    }

    delete m_shader;
    delete m_mesh;
}

void Snake::init()
{
    m_shader->bind();
    m_shader->set_uniform_mat4("projection", m_projection_matrix);
    m_shader->set_uniform_mat4("view", m_view_matrix);
    m_shader->unbind();
}

void Snake::update(float delta)
{
    m_delta_size += delta * 10.0f;

    if (m_delta_size > m_size)
    {
        m_delta_size = 0.0f;
        snake_body *head = m_body.front();
        snake_body *tail = m_body.back();

        switch (m_dir)
        {
            case EAST:
            {
                tail->position.x = head->position.x + m_size;
                tail->position.y = head->position.y;
            }
            break;
            case WEST:
            {
                tail->position.x = head->position.x - m_size;
                tail->position.y = head->position.y;
            }
            break;
            case NORTH:
            {
                tail->position.x = head->position.x;
                tail->position.y = head->position.y + m_size;
            }
            break;
            case SOUTH:
            {
                tail->position.x = head->position.x;
                tail->position.y = head->position.y - m_size;
            }
            break;
        }

        if (tail->position.x > m_screen_units - m_size)
        {
            tail->position.x = -m_screen_units + m_size;
        }
        else if (tail->position.x < -m_screen_units + m_size)
        {
            tail->position.x = m_screen_units - m_size;
        }
        else if (tail->position.y > m_screen_units - m_size)
        {
            tail->position.y = -m_screen_units + m_size;
        }
        else if (tail->position.y < -m_screen_units + m_size)
        {
            tail->position.y = m_screen_units - m_size;
        }

        m_body.push_front(tail);
        m_body.pop_back();
    }
}

void Snake::draw()
{
    m_mesh->bind();
    m_shader->bind();
    for (std::deque<snake_body *>::iterator it = m_body.begin(); it != m_body.end(); it++)
    {
        snake_body *b = *it;
        glm::mat4 m = glm::translate(m_model_matrix, b->position);
        m = glm::scale(m, glm::vec3(b->scale_factor, 0.0f));
        m_shader->set_uniform_mat4("model", m);
        m_mesh->draw();
    }
    m_shader->unbind();
    m_mesh->unbind();
}


void Snake::set_move_direction(Snake::Direction dir)
{
    if (m_dir != get_opposite_direction_of(dir))
    {
        m_dir = dir;
    }
}

Snake::Direction Snake::get_opposite_direction_of(Snake::Direction dir)
{
    switch (dir)
    {
        case EAST:
            return WEST;
        case WEST:
            return EAST;
        case NORTH:
            return SOUTH;
        default:
            return NORTH;
    }
}
