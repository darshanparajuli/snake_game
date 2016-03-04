#ifndef GAME_H_
#define GAME_H_

#include "game_window.h"
#include "snake.h"

class Game
{
    private:
        GameWindow *m_window;
        Snake *m_snake;
        bool m_running;
        bool m_paused;

    public:
        Game();
        ~Game();
        void run(void);
};

#endif
