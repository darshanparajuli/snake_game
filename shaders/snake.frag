# version 130

out vec4 color;

uniform sampler2D tex;

in vec2 tex_coord;

void main()
{
    color = texture(tex, tex_coord);
}
