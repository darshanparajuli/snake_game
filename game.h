#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <glm/glm.hpp>
#include "game_window.h"
#include "snake.h"
#include "food.h"
#include "world.h"

class Game
{
    private:
        GameWindow *m_window;

        glm::mat4 m_projection_matrix;
        glm::mat4 m_view_matrix;
        WorldSize m_world_size;

        Snake *m_snake;
        World *m_world;
        std::vector<Food *> m_foods;
        bool m_running;
        bool m_paused;

    public:
        Game();
        ~Game();
        void run(void);

    private:
        void handle_input(const SDL_Event &event);
        void update(float delta);
        void draw(void);
        void add_food(void);
};

#endif
