#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 col;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

out vec4 pos;
out vec4 colAttrib;

void main()
{
    colAttrib = col;
    gl_Position = projection * view * model * position;
    pos = projection * view * model * position;

}
