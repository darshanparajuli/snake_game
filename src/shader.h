#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

class Shader
{
private:
    int m_program;
    std::map<const char *, GLint> m_uniform_location_map;

private:
    std::string read_file(const char *file_path);

public:
    Shader();
    ~Shader();

    void init(const char *file_path_vertex, const char *file_path_fragment);
    void bind(void);
    void unbind(void);
    void set_uniform_mat4(const char *name, const glm::mat4 &matrix);
    void set_uniform_vec3(const char *name, const glm::vec3 &v);
    void set_uniform_vec4(const char *name, const glm::vec4 &v);
    GLint get_uniform_location(const char *name);

    inline int get_program() const
    {
        return m_program;
    }
};

#endif
