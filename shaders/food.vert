# version 130

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

attribute vec3 position_in;
attribute vec2 tex_coord_in;

out vec2 tex_coord;

void main()
{
    gl_Position = projection * view * model * vec4(position_in, 1.0f);
    tex_coord = tex_coord_in;
}
