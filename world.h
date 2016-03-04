#ifndef WORLD_H_
#define WORLD_H_

class World
{
    private:
        int m_row_count;
        int m_col_count;
        int **m_grid;
    
    public:
        World(int row_count, int col_count);
        ~World();
        void reset();

        inline int get_row_count() const { return m_row_count; }
        inline int get_col_count() const { return m_col_count; }
};

#endif
