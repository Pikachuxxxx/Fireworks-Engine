#include "mesh.h"

namespace fireworks { namespace graphics {

    Mesh::Mesh(Transform transform, Primitive3D primitive, Shader* shader, Texture* texture /*= nullptr*/)
        : Renderable3D(transform, maths::vec4(1, 0, 1, 1), primitive, shader, texture)
    {
        if (primitive == Primitive3D::Plane)
        {
            /*
             * 3D Plane vs Quad primitive :-
             * Same as that of a sprite but plane doesn't have any kind of face culling.
             * A Quad on the other hand would have face culling enabled by default in
             * contrast to a 3D Plane, which is visible from all sides.
             * A quad is nothing but a sprite viewed in 3D space with front face culling ON.
             * It is also a Cube's bottom face.
             */
            float ts = 0; // This will be assigned by the renderer, so we pass a default value of 0.
            vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), 0, (m_Transform.scale.y / 2)), m_UV[0], ts, m_Color));
            vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), 0, -(m_Transform.scale.y / 2)), m_UV[1], ts, m_Color));
            vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, 0, -(m_Transform.scale.y / 2)), m_UV[2], ts, m_Color));
            vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, 0, (m_Transform.scale.y / 2)), m_UV[3], ts, m_Color));

            int plane_indices[] = { 0, 1, 2, 2, 3, 0 };
            indices.insert(indices.begin(), std::begin(plane_indices), std::end(plane_indices));

        }
    }

    // TODO: Implement this
    Mesh::Mesh(std::vector<VertexData3D> verts, std::vector<GLuint>normals, std::vector<Texture> texs)
    {
        
    }

    void Mesh::setupMesh()
    {

    }

} }
