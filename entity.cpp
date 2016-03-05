#include "entity.h"
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(World *world)
    : m_world(world)
{
    m_world_size.left = 0;
    m_world_size.top = 0;
    m_world_size.right = 0;
    m_world_size.bottom = 0;
}

Entity::~Entity()
{
    m_world = 0;
}

void Entity::set_world_size(float left, float top, float right, float bottom)
{
    m_world_size.left = left;
    m_world_size.top = top;
    m_world_size.right = right;
    m_world_size.bottom = bottom;
}
