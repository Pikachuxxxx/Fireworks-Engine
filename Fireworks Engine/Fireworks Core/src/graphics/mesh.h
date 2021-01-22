#pragma once

#include "renderables/renderable3d.h"
#include "renderers/batchrenderer3d.h"
#include "renderers/shotrenderer3d.h"

namespace fireworks { namespace graphics {

    /// The 3D mesh of a 3d renderable object.
    ///
    /// Creates am complex 3d mesh of any possible shape
    class Mesh : public Renderable3D
    {
    private:
        std::vector<Texture> m_MeshTextures;
    public:
        /// Creates an empty mesh object
        Mesh() {}
        /// Creates a primitive 3d Object 
        ///
        /// @param transform The position of the 3d mesh in space
        /// @param primitive The 3D primitive to draw into the world
        /// @param shader The shader with which the mesh it to be renderer with
        /// @param texture The texture which will be applied to the 3d mesh
        Mesh(Transform transform, Primitive3D primitive, Shader* shader, Texture* texture = nullptr);
        /// Creates a complex 3d mesh by loading 3d models
        ///
        /// @param verts The vertices of the mesh
        /// @param indices The indices of the mesh
        /// @param texs The textures that will be applies to the 3d mesh
        /// @param transform The position of the mesh in space
        /// @param shader The shader with which the mesh will be rendered with
        Mesh(std::vector<VertexData3D> verts, std::vector<GLushort>indices, std::vector<Texture> texs, Transform transform, Shader* shader);
    private:
        void generateSphere(int radius, int latitudes, int longitudes);
        void generateCylinder(int topRadius, int baseRadius, int height, int sectorCount);
        void generatePlane();
        void generateCube();
    };

} }