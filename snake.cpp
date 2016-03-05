#include <iostream>
#include "snake.h"
#include <glm/gtc/matrix_transform.hpp>

Snake::Snake(World *world, glm::vec3 init_pos, int body_count)
    : Entity(world)
{
    m_size = 1.0f;
    m_delta_size = 0.0f;
    m_growth_delta = 10.0f;
    m_pause_movement = false;
    m_dir = NORTH;
    m_model_matrix = glm::mat4(1.0f);
    m_alive = true;
    m_body_count = body_count;
    m_init_pos = init_pos;

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
        glm::vec2(0.0f, 1.0f)
    };

    m_mesh = new Mesh(vertices, 4, indices, 6, tex_coord, 4);
    m_shader = new Shader();
    m_tex_snake_head = new Texture("res/textures/snake_head.png");
    m_tex_snake_body = new Texture("res/textures/snake_body.png");
}

Snake::~Snake()
{
    destroy_body();
    delete m_shader;
    delete m_mesh;
    delete m_tex_snake_head;
    delete m_tex_snake_body;
}

void Snake::init_body()
{
    for (int i = 0; i < m_body_count; i++)
    {
        snake_body *body = new snake_body();
        body->transform.position = m_init_pos - glm::vec3(0.0f, m_size * i, 0.0f);
        body->transform.scale = m_transform.scale;
        body->transform.rotation = m_transform.rotation;
        body->dir = m_dir;
        body->head = i == 0;
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
    init_body();
    m_shader->init("shaders/snake.vert", "shaders/snake.frag");

    m_tex_snake_head->load();
    m_tex_snake_body->load();

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
    m_growth_delta = 10.0f;
    m_pause_movement = false;
    m_dir = NORTH;
    m_alive = true;
}

void Snake::update(float delta)
{
    m_delta_size += delta * m_growth_delta;

    while (m_delta_size > m_size && m_alive)
    {
        m_delta_size -= m_size;
        if (m_delta_size < m_size)
        {
            m_delta_size = 0.0f;
        }
        snake_body *tail = m_body.back();
        m_world->set_value((int) tail->transform.position.y, (int) tail->transform.position.x, World::EMPTY);

        move();

        snake_body *head = m_body.front();
        if (m_world->get_value((int) head->transform.position.y, (int) head->transform.position.x) == World::SNAKE)
        {
            m_alive = false;
        }
        else
        {
            for (std::deque<snake_body *>::iterator it = m_body.begin(); it != m_body.end(); it++)
            {
                snake_body *b = *it;

                int row = (int) b->transform.position.y;
                int col = (int) b->transform.position.x;

                if (m_world->get_value(row, col) == World::FOOD)
                {
                    grow();
                    m_growth_delta += GROWTH_SPEED;
                }
                m_world->set_value(row, col, World::SNAKE);
            }
        }
    }
}

void Snake::move()
{
    snake_body *head = m_body.front();
    snake_body *tail = m_body.back();

    head->head = false;
    tail->head = true;

    switch (m_dir)
    {
        case EAST:
        {
            tail->transform.position.x = head->transform.position.x + m_size;
            tail->transform.position.y = head->transform.position.y;
        }
        break;
        case WEST:
        {
            tail->transform.position.x = head->transform.position.x - m_size;
            tail->transform.position.y = head->transform.position.y;
        }
        break;
        case NORTH:
        {
            tail->transform.position.x = head->transform.position.x;
            tail->transform.position.y = head->transform.position.y + m_size;
        }
        break;
        case SOUTH:
        {
            tail->transform.position.x = head->transform.position.x;
            tail->transform.position.y = head->transform.position.y - m_size;
        }
        break;
    }

    if (tail->transform.position.x > m_world_size.right - m_size)
    {
        tail->transform.position.x = m_world_size.left + m_size;
    }
    else if (tail->transform.position.x < m_world_size.left + m_size)
    {
        tail->transform.position.x = m_world_size.right - m_size;
    }
    else if (tail->transform.position.y > m_world_size.top - m_size)
    {
        tail->transform.position.y = m_world_size.bottom + m_size;
    }
    else if (tail->transform.position.y < m_world_size.bottom + m_size)
    {
        tail->transform.position.y = m_world_size.top - m_size;
    }

    tail->dir = m_dir;

    m_body.push_front(tail);
    m_body.pop_back();
}

void Snake::draw()
{
    m_mesh->bind();
    m_shader->bind();
    for (std::deque<snake_body *>::reverse_iterator it = m_body.rbegin(); it != m_body.rend(); it++)
    {
        snake_body *b = *it;
        if (b->head)
        {
            m_tex_snake_head->bind();
        }
        else
        {
            m_tex_snake_body->bind();
        }

        m_shader->set_uniform_mat4("model", b->transform.apply_transform(m_model_matrix));
        m_mesh->draw();

        if (b->head)
        {
            m_tex_snake_head->unbind();
        }
        else
        {
            m_tex_snake_body->unbind();
        }
    }
    m_shader->unbind();
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
        b->transform = tail->transform;
        b->head = false;

        // switch (tail->dir)
        // {
        //     case EAST:
        //     {
        //         b->transform.position.x = tail->transform.position.x - m_size;
        //         b->transform.position.y = tail->transform.position.y;
        //     }
        //     break;
        //     case WEST:
        //     {
        //         b->transform.position.x = tail->transform.position.x + m_size;
        //         b->transform.position.y = tail->transform.position.y;
        //     }
        //     break;
        //     case NORTH:
        //     {
        //         b->transform.position.x = tail->transform.position.x;
        //         b->transform.position.y = tail->transform.position.y - m_size;
        //     }
        //     break;
        //     default:
        //     {
        //         b->transform.position.x = tail->transform.position.x;
        //         b->transform.position.y = tail->transform.position.y + m_size;
        //     }
        //     break;
        // }

        b->dir = tail->dir;
        m_body.push_back(b);
    }
}

