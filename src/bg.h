#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "entity.h"
#include "mesh.h"
#include "shader.h"

class Background : public Entity
{
private:
    Shader *m_shader;
    Mesh *m_mesh;
    glm::vec3 m_snake_pos;
    glm::vec3 m_food_pos;

public:
    Background(World *world);
    ~Background();
    void init(void);
    void update(float delta);
    void draw(void);

public:
    inline void set_snake_position(glm::vec3 pos)
    {
        m_snake_pos = pos;
    }
    inline void set_food_position(glm::vec3 pos)
    {
        m_food_pos = pos;
    }
};

#endif
