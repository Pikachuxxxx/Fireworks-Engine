#version 410 core

in vec4 pos;
in vec4 colAttrib;
in vec2 uvCoords;

out vec4 color;

uniform vec2 light_pos;
uniform vec4 colour;

uniform sampler2D tex;

void main()
{
    float intensity = 1.0f / length(pos.xy - light_pos);
    color = colAttrib * intensity * colour * 0.5f;
    color = texture(tex, uvCoords);
}
