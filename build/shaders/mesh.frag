#version 410 core

in vec4 pos;
in vec2 uvCoords;
in float texID;
in vec4 colAttrib;

out vec4 color;

uniform vec4 colour = vec4(1, 0, 1, 1);
uniform sampler2D textures[16];

void main()
{
    vec4 texColor = colAttrib;
    if (texID > 0)
    {
        int tid = int(texID - 0.5);
        texColor = texture(textures[tid], uvCoords);
    }
    color = texColor;
    //color = vec4(0, 0, 0, 1);
}
