#include "src/graphics/Window.h"
#include "src/maths/maths.h"

int main()
{
    using namespace fireworks;
    using namespace graphics;
    // using namespace maths;

    Window window("fireworks !!!", 800, 600);

    glClearColor(0.8, 0.2, 0.3, 1.0f);

    maths::vec3 a(2.0f, 5.0f, 7.0f);
    maths::vec3 b(3.0, 4.0f, 5.0f);

    maths::vec3 c;
    c = a + b;
    std::cout << a << '\n';

    maths::mat4 position = maths::mat4(2.0f);
    maths::mat4 trans = maths::mat4::translation(a);
    std::cout << trans << '\n';
    trans *= position;
    std::cout << trans << '\n';


    while(!window.closed())
    {
        window.clear();
        if(window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        {
            std::cout << "Pressed" << '\n';
        }



        double tx, ty;
        window.getMousePosition(tx, ty);
        // std::cout << "Mouse X pos is : " << tx << " and Y pos is : " << ty << '\n';

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
