#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh
{
private:
    GLuint m_vao, m_vbo, m_ibo;
    unsigned int m_icount;

public:
    Mesh(glm::vec3 *vertices, int vcount, int *indices, int icount);
    ~Mesh();
    void bind(void);
    void unbind(void);
    void draw(void);
};

#endif