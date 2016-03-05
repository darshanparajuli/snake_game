#include "food.h"

Food::Food(glm::vec3 pos)
    : Entity(), m_eaten(false)
{
    m_scale = 0.65f;
    m_scale_delta = 0.5f;
    m_transform.position = pos;
    m_transform.scale = glm::vec3(0.8f, 0.8f, 1.0f);

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

    m_model_matrix = glm::mat4(1.0f);

    m_mesh = new Mesh(vertices, 4, indices, 6, tex_coord, 4);
    m_shader = new Shader();
    m_texture = new Texture("res/textures/food.png");
}

Food::~Food()
{
    delete m_texture;
    delete m_mesh;
    delete m_shader;
}

void Food::init()
{
    m_shader->init("shaders/food.vert", "shaders/food.frag");
    m_texture->load();

    m_shader->bind();
    m_shader->set_uniform_mat4("projection", m_projection_matrix);
    m_shader->set_uniform_mat4("view", m_view_matrix);
    m_shader->unbind();
}

void Food::update(float delta)
{
    m_scale += delta * m_scale_delta;

    if (m_scale > 0.8f)
    {
        m_scale = 0.8f;
        m_scale_delta = -m_scale_delta;
    }
    else if (m_scale < 0.65f)
    {
        m_scale = 0.65f;
        m_scale_delta = -m_scale_delta;
    }

    m_transform.scale.x = m_scale;
    m_transform.scale.y = m_scale;
}

void Food::draw()
{
    m_mesh->bind();
    m_texture->bind();

    m_shader->bind();
    m_shader->set_uniform_mat4("model", m_transform.apply_transform(m_model_matrix));

    m_mesh->draw();

    m_texture->unbind();
    m_shader->unbind();
    m_mesh->unbind();
}
