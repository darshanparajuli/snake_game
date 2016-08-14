#include "shader.h"
#include <GL/gl.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>

Shader::Shader() : m_program(0)
{
}
Shader::~Shader()
{
    if (m_program)
    {
        glDeleteProgram(m_program);
    }
}

void Shader::init(const char *file_path_vertex, const char *file_path_fragment)
{
    std::string vertex_source = read_file(file_path_vertex);
    std::string fragment_source = read_file(file_path_fragment);
    if (vertex_source.empty() || fragment_source.empty())
    {
        return;
    }

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *shader_src = (GLchar *) vertex_source.c_str();
    std::cout << "compiling shader: " << file_path_vertex << std::endl;
    glShaderSource(vertex_shader, 1, &shader_src, NULL);
    glCompileShader(vertex_shader);

    GLint is_compiled = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
        GLint max_length = 0;
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &max_length);
        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(vertex_shader, max_length, &max_length, &info_log[0]);
        glDeleteShader(vertex_shader);

        for (std::vector<GLchar>::const_iterator i = info_log.begin(); i != info_log.end(); i++)
        {
            std::cout << *i;
        }
        std::cout << std::endl;

        return;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shader_src = (GLchar *) fragment_source.c_str();
    std::cout << "compiling shader: " << file_path_fragment << std::endl;
    glShaderSource(fragment_shader, 1, &shader_src, 0);
    glCompileShader(fragment_shader);

    is_compiled = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE)
    {
        GLint max_length = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &max_length);
        std::vector<GLchar> info_log(max_length);
        glGetShaderInfoLog(fragment_shader, max_length, &max_length, &info_log[0]);
        glDeleteShader(fragment_shader);

        for (std::vector<GLchar>::const_iterator i = info_log.begin(); i != info_log.end(); i++)
        {
            std::cout << *i;
        }
        std::cout << std::endl;

        return;
    }

    m_program = glCreateProgram();
    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);

    glLinkProgram(m_program);

    GLint is_linked = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, (int *) &is_linked);
    if (is_linked == GL_FALSE)
    {
        GLint max_length;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &max_length);
        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(m_program, max_length, &max_length, &info_log[0]);
        glDeleteProgram(m_program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        m_program = 0;

        for (std::vector<GLchar>::const_iterator i = info_log.begin(); i != info_log.end(); i++)
        {
            std::cout << *i;
        }
        std::cout << std::endl;

        return;
    }

    glDetachShader(m_program, vertex_shader);
    glDetachShader(m_program, fragment_shader);
}

void Shader::bind()
{
    glUseProgram(m_program);
}
void Shader::unbind()
{
    glUseProgram(0);
}
void Shader::set_uniform_mat4(const char *name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set_uniform_vec3(const char *name, const glm::vec3 &v)
{
    glUniform3fv(get_uniform_location(name), 1, &v[0]);
}

void Shader::set_uniform_vec4(const char *name, const glm::vec4 &v)
{
    glUniform4fv(get_uniform_location(name), 1, &v[0]);
}

GLint Shader::get_uniform_location(const char *name)
{
    GLint location = 0;
    if (m_uniform_location_map.find(name) == m_uniform_location_map.end())
    {
        location = glGetUniformLocation(m_program, name);
        m_uniform_location_map[name] = location;
    }
    else
    {
        location = m_uniform_location_map[name];
    }
    return location;
}

std::string Shader::read_file(const char *file_path)
{
    std::string content = "";
    std::ifstream file_stream(file_path, std::ios::in);

    if (file_stream.is_open())
    {
        std::string line = "";
        while (!file_stream.eof())
        {
            std::getline(file_stream, line);
            content.append(line + "\n");
        }

        file_stream.close();
    }
    else
    {
        std::cerr << "Cannot read file " << file_path << std::endl;
    }

    return content;
}
