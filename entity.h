#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <glm/glm.hpp>
#include "transform.h"
#include "world.h"

struct WorldSize
{
    float left;
    float right;
    float top;
    float bottom;
};

class Entity
{
    protected:
        World *m_world;
        WorldSize m_world_size;
        glm::mat4 m_projection_matrix;
        glm::mat4 m_view_matrix;
        glm::mat4 m_model_matrix;
        Transform m_transform;

    public:
        Entity(World *world);
        virtual ~Entity();
        virtual void init(void) = 0;
        virtual void update(float delta) = 0;
        virtual void draw(void) = 0;
        void set_world_size(float left, float top, float right, float bottom);

    public:
        inline void set_projection_matrix(const glm::mat4 &projection) { m_projection_matrix = projection; }
        inline void set_view_matrix(const glm::mat4 &view) { m_view_matrix = view; }
        inline WorldSize* get_world_size() { return &m_world_size; }
        inline Transform* get_transform() { return &m_transform; }
        inline void set_transform(const Transform& transform) { m_transform = transform; }
};

#endif
