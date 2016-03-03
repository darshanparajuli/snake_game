#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <glm/glm.hpp>

class Entity
{
    protected:
        glm::mat4 m_projection_matrix;
        glm::mat4 m_view_matrix;
        glm::mat4 m_model_matrix;
        float m_screen_units;

    public:
        Entity() {}
        virtual ~Entity() {}
        virtual void init(void) = 0;
        virtual void update(float delta) = 0;
        virtual void draw(void) = 0;

        inline void set_projection_matrix(const glm::mat4 &projection, float units)
        {
            m_projection_matrix = projection;
            m_screen_units = units;
        }
        inline void set_view_matrix(const glm::mat4 &view) { m_view_matrix = view; }
        inline void set_model_matrix(const glm::mat4 &model) { m_model_matrix = model; }
};

#endif
