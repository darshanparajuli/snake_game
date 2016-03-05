#ifndef _FOOD_H_
#define _FOOD_H_

#include <glm/glm.hpp>
#include "entity.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Food: public Entity
{
    private:
        Mesh *m_mesh;
        Texture *m_texture;
        Shader *m_shader;
        bool m_eaten;
        float m_scale;
        float m_scale_delta;

    public:
        Food(World *world);
        ~Food();

        void init(void);
        void update(float delta);
        void draw();
        bool place_food(void);

    public:
        inline bool is_eaten() const { return m_eaten; }

};

#endif
