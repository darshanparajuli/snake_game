#include "snake.h"
#include <glm/gtc/matrix_transform.hpp>

Snake::Snake(const glm::vec3 &init_pos, float size, int body_count)
{
    m_size = size;
    m_delta_size = 0.0f;
    for (int i = 0; i < body_count; i++)
    {
        snake_body *body = new snake_body;
        body->position = init_pos + glm::vec3(0.0f, size * (float) i, 0.0f);
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
        delete *it;
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
    m_delta_size += delta * 2.0f;

    if (m_delta_size > m_size)
    {
        m_delta_size = 0.0f;
        if (m_body.size() > 0)
        {
            snake_body *head = m_body.front();
            snake_body *tail = m_body.back();
            m_body.pop_back();

            tail->position.y = head->position.y + m_size;
            m_body.push_front(tail);
        }
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
