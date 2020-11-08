#version 410 core

in vec4 pos;
in vec2 uvCoords;
in float texID;
in vec4 colAttrib;

out vec4 color;

uniform vec2 light_pos;
uniform vec4 colour = vec4(1, 0, 1, 1);
uniform sampler2D textures[16];
uniform float mixPercentage = 0.0f;

void main()
{
    float intensity = 1.0f / length(pos.xy - light_pos);
    vec4 texColor = colAttrib;
    float avgTexColor = 1.0f;
    if (texID > 0)
    {
        int tid = int(texID - 0.5);
        texColor = texture(textures[tid], uvCoords);
        avgTexColor = texColor.x + texColor.y + texColor.z / 3.0f;
    }
    if(texColor.w < 0.1f)
        discard;
    vec4 gray_color = vec4(avgTexColor, avgTexColor, avgTexColor, texColor.w) * 0.7f;
    color = mix(texColor, gray_color, mixPercentage);
}
