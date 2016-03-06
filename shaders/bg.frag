# version 130

out vec4 color;

uniform sampler2D tex;
uniform vec3 head_pos;

in vec2 tex_coord;
in vec3 position;

void main()
{
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    float dist = 1.5f / (length(position - head_pos) + 1.5f);
    color *= dist;
}
