#version 330 core

out vec4 color;

uniform vec2 light_pos;
uniform vec4 colour;

in vec4 pos;
in vec4 colAttrib;


void main()
{
    float intensity = 1.0f / length(pos.xy - light_pos);
    color = colAttrib * intensity * colour;
}
