#include "world.h"

World::World(int row_count, int col_count)
    : m_row_count(row_count), m_col_count(col_count)
{
    m_grid = new int*[row_count];
    for (int i = 0; i < row_count; i++)
    {
        m_grid[i] = new int[col_count];
    }
    reset();
}

World::~World()
{
    for (int i = 0; i < m_row_count; i++)
    {
        delete [] m_grid[i];
    }
    delete [] m_grid;
}

void World::reset()
{
    for (int i = 0; i < m_row_count; i++)
    {
        for (int j = 0; j < m_col_count; j++)
        {
            m_grid[i][j] = 0;
        }
    }
}
