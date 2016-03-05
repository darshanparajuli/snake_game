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
        void set_value(int row, int col, int val);
        int get_value(int row, int col);

    public:
        inline int get_row_count() const { return m_row_count; }
        inline int get_col_count() const { return m_col_count; }
};

#endif
