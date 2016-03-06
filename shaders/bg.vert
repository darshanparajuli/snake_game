# version 130

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

attribute vec3 position_in;
attribute vec2 tex_coord_in;

out vec2 tex_coord;
out vec3 position;

void main()
{
    gl_Position = projection * view * model * vec4(position_in, 1.0f);
    tex_coord = tex_coord_in;
    position = vec3(model * vec4(position_in, 1.0f));
}
