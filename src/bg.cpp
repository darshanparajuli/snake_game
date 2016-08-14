#include "bg.h"

Background::Background(World *world)
    : Entity(world)
{
}

Background::~Background()
{
    delete m_shader;
    delete m_mesh;
}

void Background::init()
{
    m_shader = new Shader();
    m_shader->init("shaders/bg.vert", "shaders/bg.frag");

    glm::vec3 vertices[] = {
        glm::vec3(m_world_size.left, m_world_size.top, 0.0f),
        glm::vec3(m_world_size.right, m_world_size.top, 0.0f),
        glm::vec3(m_world_size.right, m_world_size.bottom, 0.0f),
        glm::vec3(m_world_size.left, m_world_size.bottom, 0.0f)
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

    m_shader->bind();
    m_shader->set_uniform_mat4("projection", m_projection_matrix);
    m_shader->set_uniform_mat4("view", m_view_matrix);
    m_shader->unbind();
}

void Background::update(float delta)
{
}

void Background::draw()
{
    m_mesh->bind();
    m_shader->bind();

    m_transform.position = m_snake_pos;
    m_shader->set_uniform_mat4("model", m_transform.apply_transform(m_model_matrix));
    m_shader->set_uniform_vec3("pos", m_snake_pos);
    m_shader->set_uniform_vec4("diffuse", glm::vec4(1.0f, 0.5f, 0.5f, 0.7f));
    m_mesh->draw();

    m_transform.position = m_food_pos;
    m_shader->set_uniform_mat4("model", m_transform.apply_transform(m_model_matrix));
    m_shader->set_uniform_vec3("pos", m_food_pos);
    m_shader->set_uniform_vec4("diffuse", glm::vec4(0.0f, 1.0f, 1.0f, 0.7f));
    m_mesh->draw();

    m_mesh->unbind();
    m_shader->unbind();
}
