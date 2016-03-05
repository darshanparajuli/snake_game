#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include <map>
#include <glm/glm.hpp>
#include "mesh.h"
#include "shader.h"
#include "entity.h"
#include "texture.h"
#include "transform.h"

struct snake_body
{
    Transform transform;
    int dir;
    bool head;
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
        const float MOVE_SPEED = 0.1f;
        Shader *m_shader;
        Mesh *m_mesh;
        Texture *m_tex_snake_head;;
        Texture *m_tex_snake_body;
        std::deque<snake_body *> m_body;
        glm::vec3 m_init_pos;
        float m_size;
        float m_body_count;
        float m_delta_size;
        bool m_pause_movement;
        int m_dir;
        bool m_alive;
        float m_move_speed;

    public:
        Snake(World *world, glm::vec3 init_pos, int body_count);
        ~Snake();
        void init(void);
        void update(float delta);
        void draw(void);
        void set_move_direction(int dir);
        void grow(int body_count = 1);
        void reset(void);

        inline bool is_alive(void) const { return m_alive; }

    private:
        int get_opposite_direction_of(int dir);
        void init_body(void);
        void move(void);
        void destroy_body(void);
};

#endif
