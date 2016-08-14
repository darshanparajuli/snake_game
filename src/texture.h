#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>

class Texture
{
private:
    GLuint m_id;
    const char *m_path;
    int m_width;
    int m_height;

public:
    Texture(const char *file_path);
    ~Texture();
    void load();
    void bind();
    void unbind();
};

#endif
