# version 130

out vec4 color;

uniform sampler2D tex;
uniform vec3 pos;
uniform vec4 diffuse;

in vec2 tex_coord;
in vec3 position;

void main()
{
    float radius = 3.0f;
    float dist = length(position - pos);
    float intensity = clamp(1.0f - dist / radius, 0.0f, 1.0f);
    color = diffuse * intensity;
}
