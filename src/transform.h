#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>

class Transform
{
private:
    glm::vec3 m_axis;
    ;

public:
    glm::vec3 position;
    float rotation;  // degrees
    glm::vec3 scale;

public:
    Transform();
    ~Transform();
    glm::mat4 apply_transform(const glm::mat4 &model);
};

#endif
