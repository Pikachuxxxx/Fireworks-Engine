#pragma once

#include "renderables/renderable3d.h"
#include "renderers/batchrenderer3d.h"
#include "renderers/shotrenderer3d.h"

namespace fireworks { namespace graphics {

    class Mesh : public Renderable3D
    {
    public:
        Mesh(Transform transform, Primitive3D primitive, Shader* shader, Texture* texture = nullptr);
    protected:
        Mesh(std::vector<VertexData3D> verts, std::vector<GLuint>normals, std::vector<Texture> texs);
    private:
        void setupMesh();
    };

} }