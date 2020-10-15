#version 410 core

in vec4 pos;
in vec2 uvCoords;
in float texID;
in vec4 colAttrib;

out vec4 color;

uniform vec2 light_pos;
uniform vec4 colour;
uniform sampler2D textures[16];

void main()
{
    float intensity = 1.0f / length(pos.xy - light_pos);
    vec4 texColor = colAttrib;
    if (texID > 0)
    {
        int tid = int(texID - 0.5);
        texColor = texture(textures[tid], uvCoords);
        if(texColor.a < 0.1)
            discard;
    }
    color = texColor;// * intensity * 0.5f;
}
