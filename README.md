<p align="center">
  <img width=300" src="https://github.com/Pikachuxxxx/Fireworks-Engine/blob/master/fireworks%20logo.png">
</p>
<h1 align="center"> Fireworks Engine </h1>

<p align="center">
<h3 align="center">A Lightweight Sandbox Game Engine using OpenGL for additional Customisation and Quick Prototyping.</h3>
</p>

<p align="center">
  <a href="#features">Features</a> |
  <a href="#building">Building</a> |
  <a href="#usage">Usage</a> |
  <a href="https://github.com/Pikachuxxxx/Fireworks-Engine/wiki">API/Docs</a> |
  <a href="#dependencies">Dependencies</a>
<br/>
</p>  

<p align="center">  
<br/>
<a href="https://github.com/Pikachuxxxx/Fireworks-Engine"><img alt="platforms" src="https://img.shields.io/badge/Platforms-Windows%20%7C%20Linux%20%7C%20macOS%20%7C-blue?style=flat-square"/>  </a>       
<a href="https://github.com/Pikachuxxxx/Fireworks-Engine/blob/master/LICENSE"><img alt="license" src="https://img.shields.io/github/license/Pikachuxxxx/fireworks-engine?style=flat-square"/>  </a>
<br/>
<a href="https://github.com/Pikachuxxxx/Fireworks-Engine/issues"><img alt="Issues" src="https://img.shields.io/github/issues/Pikachuxxxx/fireworks-engine?style=flat-square"/></a>
<a href=""><img alt="size" src="https://img.shields.io/github/repo-size/Pikachuxxxx/fireworks-engine?color=FFA500&style=flat-square"/></a>
<br/>
</p>

### About
Basically a HelloWorld but this time it's for an entire game engine.

**Updates :**

Currently working on Camera2D and adding Render and Frame buffers (FBO, RBO for textures mapping) to the Renderer2D.

Find the latest features list and updates about the engine at : [Fireworks Engine update thread](https://twitter.com/GameGraphicsGuy/status/1300449455733239808)

#
### Features

- 2D rendering pipeline
- Can render upto 60, 000 Sprites, textures using batch rendering
- Simple and customisable math library
- Basic font rendering (supports only a single font for now)
- Easy to manage and customisable native scripting 
- Simple API for faster development and customisation
- Simple Window and Input management System 
- and a lot more on the way....

#
### Building
**MacOS/Windows/Linux :**
  change to the build folder and use the CMakeFile to generate the MakeFile and build the library using the Make command
```bash
  mkdir build
  cd build 
  cmake ..
  make 
```

### Usage
**Find more Examples in the Sandbox project [here](https://github.com/Pikachuxxxx/Fireworks-Engine/tree/master/Fireworks%20Engine/Sandbox/examples)**

Here's an example to render a simple coloured square. [simplebox.h](https://github.com/Pikachuxxxx/Fireworks-Engine/blob/master/Examples/SimpleBox.h)
```cpp

#include <fireworks/fireworks.h>

using namespace fireworks;

class SimpleBox : public Fireworks
{
private:
    Window* window;
    Layer* layer;
public:
    SimpleBox() { }

    ~SimpleBox()
    {
        delete layer;
    }

    // Runs once per initialisation
    void init() override
    {
        window = createWindow("Test Game Example : Fireworks Engine", 800, 600);
        layer = new Layer(new BatchRenderer2D(),
                          new Shader("../Fireworks-core/src/shaders/basic.vert",
                                     "../Fireworks-core/src/shaders/basic.frag"),
                          mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f , 1.0f));

        Sprite* box = new Sprite(4.0f, 4.0f, 4.0f, 4.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f));
        layer->add(box);
   }

   // Runs once per second
    void tick() override { }

    // Runs 60 times per second
    void update() override { }

    // Runs as fast as possible
    void render() override
    {
        layer->render();
    }
};

int main()
{
    SimpleBox game;
    game.start();
    return 0;
}
```
### TODO
- Camera 2D
- Render textures and Frame Buffer objects
- Physics2D component (box2d physics engine integration)
- Better and customisable font rendering 
- Audio system
- Materials and Lights (2D and 3D)
- Event system
- 3D rendering + BatchRenderer3D
- Camera 3D
- 2D + 3D primitive drawing utility function 
- 3D Physics 
- ECS - entity component system 
- Occlusion Culling

#
### Dependencies
- [SOIL](https://github.com/Pikachuxxxx/SOIL), Freetype and [glText](https://github.com/vallentin/glText), GLEW, GLFW, PNG, Zlib2 

