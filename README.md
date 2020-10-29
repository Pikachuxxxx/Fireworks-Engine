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
  <a href="https://fireworks-engine.readthedocs.io/en/latest/">API/Docs</a> |
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
<a href='https://fireworks-engine.readthedocs.io/en/latest/?badge=latest'><img src='https://readthedocs.org/projects/fireworks-engine/badge/?version=latest' alt='Documentation Status' />
</a>

<br/>
</p>

### About
Basically a HelloWorld but this time it's for an entire game engine.

### Ludum Dare 47
- Checkout branch [LD47](https://github.com/Pikachuxxxx/Fireworks-Engine/tree/LD47/Fireworks%20Engine/LD47) for my [ludum dare submissoin](https://ldjam.com/events/ludum-dare/47/one-for-an-era) using fireworks engine, a lot of experimental features were added during the jam that will soon be integrated into the engine.

### Updates

Currently Event system and adding more diversity to the existing API.

Find the latest features list and updates about the engine at : [Fireworks Engine update thread](https://twitter.com/GameGraphicsGuy/status/1300449455733239808)

#
### Features

- 2D rendering pipeline
- Can render upto 60, 000 Sprites, textures using batch rendering
- Sprite Sheet Animations (can change frame or frame rate manually, supports 2 types of in-built animation modes [LOOP, PING_PONG])
- Simple and customisable math library
- TrueType Font Rendering (currently only supports (.TTF) UTF-8 characters)
- Easy to manage and customisable native scripting 
- Simple API for faster development and customisation
- Simple Window and Input management System 
- Huge custom Maths Library and a lot of utility functions
- Render textures and Frame Buffer objects
- 2D orthographic camera 
- Suppports 2D and 3D Audio with an extensive API (OpenAL backend) (currenlty only reads .wav files)

#
### Building
**Windows :**
- **Use the Visual Studio Solution to build the engine and work with the Sandbox.**

**MacOS/Linux :**
  change to the build folder and use the CMakeFile to generate the MakeFile and build the library using the Make command
```bash
  mkdir build
  cd build 
  #use this to build the library
  cmake .. -DBUILD_STATIC_LIBRARY=true
  make 
  #now remove the CMakeChache to generate the sandbox executable
  rm -rf CMakeCache.txt
  cmake .. -DBUILD_SANDBOX_EXEC=true
  make
  #Now run the exectubale (Just include the example file or your custom game headers in the SandBox.cpp)
  ./SandBox
```
### Documentation
Find the comlpete documentation, API reference and examples usage [here](https://fireworks-engine.readthedocs.io/en/latest/)
### Usage
### Find more Examples in the Sandbox project [here](https://github.com/Pikachuxxxx/Fireworks-Engine/tree/master/Fireworks%20Engine/Sandbox/examples)

Checkout the example of Space Shooter game to get an understanding of the capabilites of the engine. [Zapper.h](https://github.com/Pikachuxxxx/Fireworks-Engine/blob/master/Fireworks%20Engine/Sandbox/examples/Zapper.h)

Here's an example to render a simple coloured square. [simplebox.h](https://github.com/Pikachuxxxx/Fireworks-Engine/blob/master/Examples/SimpleBox.h)
```cpp

#include <fireworks/fireworks.h>

using namespace fireworks;

class SimpleBox : public Fireworks
{
private:
    Window*     window;
    Camera2D*   camera;
    Layer*      layer;
public:
    SimpleBox() { }

    ~SimpleBox()
    {
        delete layer;
    }

    // Runs once per initialization
    void init() override
    {
        // Initialize the window and set it's properties
        window = createWindow("Simple Box Example : Fireworks Engine", 800, 600);
        // Initialize the Camera and set the Projection Matrix
        camera = new Camera2D(mat4::orthographic(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f));

        // Create the Renderer using a shader and pass the cam onto which you wish to render
        Shader* basicShader = new Shader(".\\shaders\\basic.vert", ".\\shaders\\basic.frag");
        BatchRenderer2D* batchRenderer = new BatchRenderer2D(camera, basicShader);

        // Pass a renderer to the layer to render the renderables in that layer using that renderer
        layer = new Layer(batchRenderer);

        // Now create and add the renderables to the layer
        Sprite* box = new Sprite(vec3(0, 0, 0), vec2(4, 4), vec4(1, 1, 0, 1));
        layer->add(box);
    }

   // Runs once per second
	void tick() override { }

    // Runs 60 times per second
    void update() override { }

    // Runs as fast as possible
    void render() override 
    {
        // Render the Layer
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
- [x] Camera 2D
- [x] Render textures and Frame Buffer objects
- [x] Sprite Sheet Animations
- [x] TTF Font Rendering and font properties(position, color etc.)
- [x] 2D Audio (OpenAL backend)
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
- Editor UI using ImGui

#
### Dependencies
- [SOIL](https://github.com/Pikachuxxxx/SOIL), Freetype and [glText](https://github.com/vallentin/glText), GLEW, GLFW, PNG, Zlib2, stb_image, OpenAL

