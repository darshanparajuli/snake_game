# version 130

out vec4 color;

uniform sampler2D tex;
uniform vec3 head_pos;

in vec2 tex_coord;
in vec3 position;

void main()
{
    float dist = length(position - head_pos);
    float intensity = clamp(1.0f - dist / 1.0f, 0.0f, 1.0f);
    color = texture(tex, tex_coord) * 0.8f;
    color.a = 1.0f;
}
