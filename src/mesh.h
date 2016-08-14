#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
private:
    GLuint m_vao, m_vbo, m_ibo, m_tbo;
    unsigned int m_icount;

public:
    Mesh(glm::vec3 *vertices, int vcount, int *indices, int icount, glm::vec2 *tex_coord, int tcount);
    ~Mesh();
    void bind(void);
    void unbind(void);
    void draw(void);
};

#endif
