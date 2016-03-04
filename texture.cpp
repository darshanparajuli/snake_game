#include "texture.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Texture::Texture(char *file_path)
    : m_id(0), m_path(file_path), m_width(0), m_height(0)
{
}

Texture::~Texture()
{
    if (m_id)
    {
        glDeleteTextures(1, &m_id);
    }
}

bool Texture::load()
{
    SDL_Surface *surface = IMG_Load(m_path);
    if (!surface)
    {
        std::cerr << "Error loading image: " << m_path << std::endl;
        return false;
    }

    int mode;
    if (surface->format->BytesPerPixel == 3)
    {
        mode = GL_RGB;
    }
    else if (surface->format->BytesPerPixel == 4)
    {
        mode = GL_RGBA;
    }
    else
    {
        std::cerr << "Error detecting mode" << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    m_width = surface->w;
    m_height = surface->h;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, mode, m_width, m_height, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(surface);

    return true;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
