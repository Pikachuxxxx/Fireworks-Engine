#include "src/graphics/Window.h"
#include "src/graphics/Shader.h"
#include "src/maths/maths.h"
#include "src/utils/fileutils.h"

int main()
{
    using namespace fireworks;
    using namespace graphics;
    using namespace maths;
    using namespace utils;

    Window window("fireworks !!!", 800, 600);
    // glClearColor(0.8, 0.2, 0.3, 1.0f);



    GLfloat vertices[] = {
        4, 3, 0,
        12, 6, 0,
        4, 6, 0
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);




    Shader shader("fireworks-core/src/shaders/basic.vert", "fireworks-core/src/shaders/basic.frag");
    shader.enable();
    shader.setUniformMat4("projection", ortho);
    // shader.setUniformMat4("model", mat4::rotation(45.0f, vec3(0.0f, 0.0f, 1.0f)));

    shader.setUniform2f("light_pos", vec2(6.0f, 5.0f));
    shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while(!window.closed())
    {
        window.clear();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.update();
    }

    return 0;
}
