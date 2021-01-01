#include "mesh.h"

namespace fireworks { namespace graphics {

    Mesh::Mesh(Transform transform, Primitive3D primitive, Shader* shader, Texture* texture /*= nullptr*/)
        : Renderable3D(transform, maths::vec4(1, 0, 1, 1), primitive, shader, texture)
    {
        if (primitive == Primitive3D::Plane)
            generatePlane();
        else if (primitive == Primitive3D::Cube)
            generateCube();
    }

    Mesh::Mesh(std::vector<VertexData3D> verts, std::vector<GLushort>indices, std::vector<Texture> texs, Transform transform, Shader* shader)
        : Renderable3D(transform, maths::vec4(1, 0, 1, 1), Primitive3D::None, shader)
    {
        m_Vertices.insert(m_Vertices.end(), verts.begin(), verts.end());
        m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
        m_MeshTextures.insert(m_MeshTextures.end(), texs.begin(), texs.end());
        std::cout << "Textures count is : " << m_MeshTextures.size() << std::endl;
        //m_Texture = new Texture(m_MeshTextures[0]);
    }

    void Mesh::generatePlane()
    {
        /*
        * 3D Plane vs Quad primitive :-
        * Same as that of a sprite but plane doesn't have any kind of face culling.
        * A Quad on the other hand would have face culling enabled by default in
        * contrast to a 3D Plane, which is visible from all sides.
        * A quad is nothing but a sprite viewed in 3D space with front face culling ON.
        * It is also a Cube's bottom face.
        * Note:- Here we only use the X and Y coordinates of the scale as Z-depth doesn't make any sense for a 3D plane. 
        */
        float ts = 0; // This will be assigned by the renderer, so we pass a default value of 0.
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), 0, (m_Transform.scale.y / 2)), m_UV[0], ts, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), 0, -(m_Transform.scale.y / 2)), m_UV[1], ts, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, 0, -(m_Transform.scale.y / 2)), m_UV[2], ts, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, 0, (m_Transform.scale.y / 2)), m_UV[3], ts, m_Color));

        GLushort plane_indices[] = { 0, 1, 2, 2, 3, 0 };
        m_Indices.insert(m_Indices.begin(), std::begin(plane_indices), std::end(plane_indices));
    }

    void Mesh::generateCube()
    {
        // Face 1 : Front face
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[0], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2) + m_Transform.scale.y, (m_Transform.scale.z / 2)), m_UV[1], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2) + m_Transform.scale.y, (m_Transform.scale.z / 2)), m_UV[2], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[3], 0, m_Color));
        GLushort i1[] = { 0, 1, 2, 2, 3, 0 };
        m_Indices.insert(m_Indices.begin(), std::begin(i1), std::end(i1));

        // Face 2 : Top face
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), (m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[4], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), (m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[5], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, (m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[6], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, (m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[7], 0, m_Color));
        GLushort i2[] = { 4, 5, 6, 6, 7, 4 };
        m_Indices.insert(m_Indices.begin(), std::begin(i2), std::end(i2));

        // Face 3 : Back face
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[8], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2) + m_Transform.scale.y, -(m_Transform.scale.z / 2)), m_UV[9], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2) + m_Transform.scale.y, -(m_Transform.scale.z / 2)), m_UV[10], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[11], 0, m_Color));
        GLushort i3[] = { 8, 9, 10, 10, 11, 8 };
        m_Indices.insert(m_Indices.begin(), std::begin(i3), std::end(i3));

        // Face 4 : Bottom face
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[12], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[13], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[14], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[15], 0, m_Color));
        GLushort i4[] = { 12, 13, 14, 14, 15, 12 };
        m_Indices.insert(m_Indices.begin(), std::begin(i4), std::end(i4));

        // Face 5 : Right face
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[16], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2) + m_Transform.scale.y, (m_Transform.scale.z / 2)), m_UV[17], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2) + m_Transform.scale.y, -(m_Transform.scale.z / 2)), m_UV[18], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2) + m_Transform.scale.x, -(m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[19], 0, m_Color));
        GLushort i5[] = { 16, 17, 18, 18, 19, 16 };
        m_Indices.insert(m_Indices.begin(), std::begin(i5), std::end(i5));

        // Face 6 : Left face
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2), (m_Transform.scale.z / 2)), m_UV[20], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2) + m_Transform.scale.y, (m_Transform.scale.z / 2)), m_UV[21], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2) + m_Transform.scale.y, -(m_Transform.scale.z / 2)), m_UV[22], 0, m_Color));
        m_Vertices.push_back(VertexData3D(maths::vec3(-(m_Transform.scale.x / 2), -(m_Transform.scale.y / 2), -(m_Transform.scale.z / 2)), m_UV[23], 0, m_Color));
        GLushort i6[] = { 20, 21, 22, 22, 23, 20 };
        m_Indices.insert(m_Indices.begin(), std::begin(i6), std::end(i6));
    }

    void Mesh::generateSphere(int radius, int latitudes, int longitudes)
    {

    }

    void Mesh::generateCylinder(int topRadius, int bottomRadius, int height, int sectors)
    {

    }

} }
