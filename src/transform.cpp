#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_axis = glm::vec3(0.0f, 0.0f, 1.0f);
    rotation = 0;
    scale = glm::vec3(1.0f, 1.0f, 0.0f);
}

Transform::~Transform()
{
}

glm::mat4 Transform::apply_transform(const glm::mat4 &model)
{
    glm::mat4 m = glm::translate(model, position);
    m = glm::rotate(m, rotation, m_axis);
    m = glm::scale(m, scale);
    return m;
}
