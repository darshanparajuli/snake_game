#ifndef GAME_H_
#define GAME_H_

#include <glm/glm.hpp>
#include "game_window.h"
#include "snake.h"
#include "food.h"
#include "world.h"
#include "bg.h"

class Game
{
    private:
        GameWindow *m_window;

        glm::mat4 m_projection_matrix;
        glm::mat4 m_view_matrix;
        WorldSize m_world_size;

        Background *m_background;
        Snake *m_snake;
        Food *m_food;
        World *m_world;
        bool m_running;
        bool m_paused;
        bool m_initial_pause;

    public:
        Game();
        ~Game();
        void run(void);

    private:
        void handle_input(const SDL_Event &event);
        void update(float delta);
        void draw(void);
        void reset(void);
};

#endif
