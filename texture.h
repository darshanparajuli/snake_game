#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>

class Texture
{
    private:
        GLuint m_id;
        char *m_path;
        int m_width;
        int m_height;

    public:
        Texture(char *file_path);
        ~Texture();
        bool load();
        void bind();
        void unbind();

        inline int get_width() const { return m_width; }
        inline int get_height() const { return m_height; }
};

#endif
