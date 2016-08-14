#include "entity.h"
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(World *world) : m_world(world)
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
void Entity::set_world_size(WorldSize world_size)
{
    m_world_size = world_size;
}
