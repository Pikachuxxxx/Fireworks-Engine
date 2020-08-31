#include "src/graphics/Window.h"


int main()
{
    using namespace fireworks;
    using namespace graphics;

    Window window("fireworks !!!", 800, 600);

    glClearColor(0.8, 0.2, 0.3, 1.0f);

    while(!window.closed())
    {
        window.clear();
        if(window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        {
            std::cout << "Pressed" << '\n';
        }

        double tx, ty;
        window.getMousePosition(tx, ty);
        std::cout << "Mouse X pos is : " << tx << " and Y pos is : " << ty << '\n';
        // glBegin(GL_QUADS);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(-0.5f,  0.5f);
        // glVertex2f( 0.5f,  0.5f);
        // glVertex2f( 0.5f, -0.5f);
        // glEnd();
        window.update();
    }

    return 0;
}
