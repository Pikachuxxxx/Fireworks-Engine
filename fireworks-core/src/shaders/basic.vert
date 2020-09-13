#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 col;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

out vec4 pos;
out vec4 colAttrib;
out vec2 uvCoords;

void main()
{
    pos = projection * view * model * position;
    gl_Position = pos;
    colAttrib = col;
    uvCoords = vec2(uv.x, 1.0f - uv.y);
}
