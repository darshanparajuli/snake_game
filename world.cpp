#include "world.h"
#include <iostream>

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

void World::set_value(int row, int col, int value)
{
    row += m_row_count / 2;
    col += m_col_count / 2;
    m_grid[row][col] = value;
}

int World::get_value(int row, int col)
{
    row += m_row_count / 2;
    col += m_col_count / 2;
    return m_grid[row][col];
}

void World::print()
{
    std::cout << "World" << std::endl;
    for (int r = 0; r < m_row_count; r++)
    {
        for (int c = 0; c < m_col_count; c++)
        {
            std::cout << m_grid[r][c] << " ";
        }
        std::cout << std::endl;
    }
}
