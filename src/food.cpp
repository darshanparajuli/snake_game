#include "food.h"
#include <vector>

Food::Food(World *world)
    : Entity(world)
{
    m_eaten = false;
    m_scale = 1.0f;
    m_rotation = 0.0f;
    m_rotation_delta = 1.5f;
    m_scale_delta = 0.75f;
    m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

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

    place_food();
}

void Food::update(float delta)
{
    m_scale += delta * m_scale_delta;
    m_rotation += delta * m_rotation_delta;

    if (m_scale > 1.0f)
    {
        m_scale = 1.0f;
        m_scale_delta = -m_scale_delta;
    }
    else if (m_scale < 0.5f)
    {
        m_scale = 0.5f;
        m_scale_delta = -m_scale_delta;
    }

    if (m_rotation > 360.0f)
    {
        m_rotation = 0.0f;
    }

    m_transform.scale.x = m_scale;
    m_transform.scale.y = m_scale;
    m_transform.rotation = m_rotation;

    int row = (int) m_transform.position.y;
    int col = (int) m_transform.position.x;
    if (!m_eaten && m_world->get_value(row, col) == World::SNAKE)
    {
        m_eaten = true;
    }
}

bool Food::place_food()
{
    std::vector<int> empty_rows(m_world->get_row_count());
    std::vector<int> empty_cols(m_world->get_col_count());
    for (int i = m_world_size.bottom + 1; i < m_world_size.top; i++)
    {
        for (int j = m_world_size.left + 1; j < m_world_size.right; j++)
        {
            if (m_world->get_value(i, j) == World::EMPTY)
            {
                empty_rows.push_back(i);
                empty_cols.push_back(j);
            }
        }
    }

    if (empty_rows.size() > 0 && empty_cols.size() > 0)
    {
        int row = empty_rows[std::rand() % empty_rows.size()];
        int col = empty_cols[std::rand() % empty_cols.size()];
        m_transform.position.x = col;
        m_transform.position.y = row;
        m_world->set_value(row, col, World::FOOD);
        m_eaten = false;
        return true;
    }

    return false;
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
