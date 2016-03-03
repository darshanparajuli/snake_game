#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include <glm/glm.hpp>
#include "mesh.h"
#include "shader.h"
#include "entity.h"

struct snake_body
{
    glm::vec3 position;
    glm::vec2 scale_factor;
    int dir;
};

class Snake : public Entity
{
    public:
        enum Direction
        {
            EAST,
            WEST,
            NORTH,
            SOUTH
        };

    private:
        Shader *m_shader;
        Mesh *m_mesh;
        std::deque<snake_body *> m_body;
        float m_size;
        float m_delta_size;
        bool m_pause_movement;
        int m_dir;

    public:
        Snake(const glm::vec3 &init_pos, float size, int body_count);
        ~Snake();
        void init(void);
        void update(float delta);
        void draw(void);
        void set_move_direction(int dir);
        void grow(int body_count);

    private:
        int get_opposite_direction_of(int dir);
};

#endif
