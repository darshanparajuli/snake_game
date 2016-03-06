# version 130

out vec4 color;

uniform sampler2D tex;
uniform vec3 head_pos;

in vec2 tex_coord;
in vec3 position;

void main()
{
    color = texture(tex, tex_coord);
    float dist = 5.0f / (length(position - head_pos) + 4.0f);
    color *= dist;
}
