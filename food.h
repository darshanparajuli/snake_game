#ifndef _FOOD_H_
#define _FOOD_H_

#include <glm/glm.hpp>
#include "entity.h"

class Food: public Entity
{
private:
    glm::vec3 m_pos;
    glm::vec3 m_color;

public:
    Food(glm::vec3 &pos, glm::vec3 &color);
    ~Food();

    void update(float delta);
    void render();

    inline glm::vec3 get_position() const { return m_pos; }
    inline glm::vec3 get_color() const { return m_color; }
};

#endif
