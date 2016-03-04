#include <iostream>
#include "snake.h"
#include <glm/gtc/matrix_transform.hpp>

Snake::Snake(const glm::vec3 &init_pos, float size, int body_count)
{
    m_size = (size <= 0) ? 1 : size;
    m_delta_size = 0.0f;
    m_pause_movement = false;
    m_dir = NORTH;
    m_model_matrix = glm::mat4(1.0f);
    m_alive = true;
    m_body_count = body_count;
    m_init_pos = init_pos;

    init_body();

    glm::vec3 vertices[] = {
        glm::vec3(-0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f)
    };
    int indices[] = {0, 1, 2, 0, 2, 3};

    glm::vec2 tex_coord[] = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f)
    };

    m_mesh = new Mesh(vertices, 4, indices, 6, tex_coord, 4);

    m_shader = new Shader();
    m_shader->init("shaders/snake.vert", "shaders/snake.frag");

    m_texture = new Texture("res/textures/block.png");
}

Snake::~Snake()
{
    destroy_body();
    delete m_shader;
    delete m_mesh;
}

void Snake::init_body()
{
    for (int i = 0; i < m_body_count; i++)
    {
        snake_body *body = new snake_body();
        body->position = m_init_pos - glm::vec3(0.0f, m_size * i, 0.0f);
        body->scale_factor = glm::vec2(0.8f, 0.8f);
        body->dir = m_dir;
        m_body.push_back(body);
    }
}

void Snake::destroy_body()
{
    for (std::deque<snake_body *>::iterator it = m_body.begin(); it != m_body.end(); it++)
    {
        if (*it)
        {
            delete *it;
        }
    }
    m_body.clear();
}

void Snake::init()
{
    m_texture->load();
    m_shader->bind();
    m_shader->set_uniform_mat4("projection", m_projection_matrix);
    m_shader->set_uniform_mat4("view", m_view_matrix);
    m_shader->unbind();
}

void Snake::reset()
{
    destroy_body();
    init_body();
    m_delta_size = 0.0f;
    m_pause_movement = false;
    m_dir = NORTH;
    m_alive = true;
}

void Snake::update(float delta)
{
    m_delta_size += delta * 10.0f;

    if (m_delta_size > m_size && m_alive)
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

        tail->dir = m_dir;

        m_body.push_front(tail);
        m_body.pop_back();

        m_alive = !check_dead();
    }
}

bool Snake::check_dead()
{
    snake_body *head = m_body.front();
    std::deque<snake_body *>::iterator it = m_body.begin();
    it++;
    while (it != m_body.end())
    {
        snake_body *b = *it;
        if (b->position.x == head->position.x && b->position.y == head->position.y)
        {
            return true;
        }
        it++;
    }
    return false;
}

void Snake::draw()
{
    m_mesh->bind();
    m_texture->bind();
    m_shader->bind();
    for (std::deque<snake_body *>::reverse_iterator it = m_body.rbegin(); it != m_body.rend(); it++)
    {
        snake_body *b = *it;
        glm::mat4 m = glm::translate(m_model_matrix, b->position);
        m = glm::scale(m, glm::vec3(b->scale_factor, 0.0f));
        m_shader->set_uniform_mat4("model", m);
        m_mesh->draw();
    }
    m_shader->unbind();
    m_texture->unbind();
    m_mesh->unbind();
}


void Snake::set_move_direction(int dir)
{
    if (m_body.front()->dir != get_opposite_direction_of(dir))
    {
        m_dir = dir;
    }
}

int Snake::get_opposite_direction_of(int dir)
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

void Snake::grow(int body_count)
{
    for (int i = 0; i < body_count; i++)
    {
        snake_body *b = new snake_body();
        snake_body *tail = m_body.back();
        b->scale_factor = tail->scale_factor;

        switch (tail->dir)
        {
            case EAST:
            {
                b->position.x = tail->position.x - m_size;
                b->position.y = tail->position.y;
            }
            break;
            case WEST:
            {
                b->position.x = tail->position.x + m_size;
                b->position.y = tail->position.y;
            }
            break;
            case NORTH:
            {
                b->position.x = tail->position.x;
                b->position.y = tail->position.y - m_size;
            }
            break;
            default:
            {
                b->position.x = tail->position.x;
                b->position.y = tail->position.y + m_size;
            }
            break;
        }

        b->dir = tail->dir;
        m_body.push_back(b);
    }
}

