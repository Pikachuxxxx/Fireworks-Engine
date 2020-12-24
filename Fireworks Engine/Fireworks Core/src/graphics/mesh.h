#pragma once

#include "renderables/renderable3d.h"
#include "renderers/batchrenderer3d.h"
#include "renderers/shotrenderer3d.h"

namespace fireworks { namespace graphics {

    class Mesh : public Renderable3D
    {
    private:
        std::vector<Texture> m_MeshTextures;
    public:
        Mesh() {}
        Mesh(Transform transform, Primitive3D primitive, Shader* shader, Texture* texture = nullptr);
        Mesh(std::vector<VertexData3D> verts, std::vector<GLushort>indices, std::vector<Texture> texs, Transform transform, Shader* shader);
    private:
        void generatePlane();
        void generateCube();
    };

} }