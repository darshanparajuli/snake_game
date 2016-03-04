#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include <map>
#include <glm/glm.hpp>
#include "mesh.h"
#include "shader.h"
#include "entity.h"
#include "texture.h"

struct snake_body
{
    glm::vec3 position;
    glm::vec2 scale_factor;
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

    public:
        Snake(const glm::vec3 &init_pos, float size, int body_count);
        ~Snake();
        void init(void);
        void update(float delta);
        void draw(void);
        void set_move_direction(int dir);
        void grow(int body_count);
        void reset(void);

        inline bool is_alive(void) const { return m_alive; }

    private:
        int get_opposite_direction_of(int dir);
        bool check_dead(void);
        void init_body(void);
        void destroy_body(void);
};

#endif
