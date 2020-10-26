#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 col;

out vec4 pos;
out vec2 uvCoords;
out float texID;
out vec4 colAttrib;

uniform mat4 projection;
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

uniform bool flipX = false;
uniform bool flipY = false;

void main()
{
    pos = projection * view * model * position;
    gl_Position = pos;

    float uvX = !flipX ? uv.x : 1.0f - uv.x;
    float uvY = !flipY ? uv.y : 1.0f - uv.y;
    uvCoords = vec2(uvX, uvY);
    texID = tid;
    colAttrib = col;
}
