#include "mesh.h"

namespace fireworks { namespace graphics {

    Mesh::Mesh(Transform transform, Primitive3D primitive, Shader* shader, Texture* texture /*= nullptr*/)
        : Renderable3D(transform, maths::vec4(1, 0, 1, 1), primitive, shader, texture)
    {
        if (primitive == Primitive3D::Plane)
            generatePlane();
        else if (primitive == Primitive3D::Cube)
            generateCube();
        else if (primitive == Primitive3D::UVSphere)
            generateSphere(1, 10, 10);
        else if (primitive == Primitive3D::Cylinder)
            generateCylinder(1, 1, 1, 10);

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

    void Mesh::generateSphere(int radius, int latitudes, int longitudes)
    {
        if (longitudes < 3)
            longitudes = 3;
        if (latitudes < 2)
            latitudes = 2;

        std::vector<VertexData3D> vertices;
        //std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        float nx, ny, nz, lengthInv = 1.0f / radius;
        float deltaLatitude = M_PI / latitudes;
        float deltaLongitude = 2 * M_PI / longitudes;
        float latitudeAngle;
        float longitudeAngle;

        // Compute all vertices first except normals
        for (int i = 0; i <= latitudes; ++i)
        {
            latitudeAngle = M_PI / 2 - i * deltaLatitude;           /* Starting -pi/2 to pi/2 */
            float xy = radius * cosf(latitudeAngle);                /* r * cos(phi) */
            float z = radius * sinf(latitudeAngle);                 /* r * sin(phi )*/

            /*
             * We add (latitudes + 1) vertices per longitude because of equator,
             * the North pole and South pole are not counted here, as they overlap.
             * The first and last vertices have same position and normal, but
             * different Tex Coords.
             */
            for (int j = 0; j <= longitudes; ++j)
            {
                longitudeAngle = j * deltaLongitude;

                VertexData3D vertex;
                vertex.vertex.x = xy * cosf(longitudeAngle);        /* x = r * cos(phi) * cos(theta)  */
                vertex.vertex.y = xy * sinf(longitudeAngle);        /* y = r * cos(phi) * sin(theta) */
                vertex.vertex.z = z;                                /* z = r * sin(phi) */
                vertex.uv.x = (float)j / longitudes;                /* s */
                vertex.uv.y = (float)i / latitudes;                 /* t */
                vertex.tid = 0.0f;
                vertex.color = m_Color;
                vertices.push_back(vertex);

                // normalized vertex normal
               /* nx = vertex.x * lengthInv;
                ny = vertex.y * lengthInv;
                nz = vertex.z * lengthInv;
                normals.push_back(glm::vec3(nx, ny, nz));*/
            }
        }

        /*
         *  Indices
         *  k1--k1+1
         *  |  / |
         *  | /  |
         *  k2--k2+1
         */
        unsigned int k1, k2;
        for (int i = 0; i < latitudes; ++i)
        {
            k1 = i * (longitudes + 1);
            k2 = k1 + longitudes + 1;
            // 2 Triangles per latitude block excluding the first and last longitudes blocks
            for (int j = 0; j < longitudes; ++j, ++k1, ++k2)
            {
                if (i != 0)
                {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if (i != (latitudes - 1))
                {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        m_Vertices.insert(m_Vertices.begin(), vertices.begin(), vertices.end());
        m_Indices.insert(m_Indices.begin(), indices.begin(), indices.end());
    }

    void Mesh::generateCylinder(int topRadius, int baseRadius, int height, int sectorCount)
    {

        std::vector<VertexData3D> vertices;
        //std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
        float x, y, z;                                  // vertex position
        float radius;                                   // radius for each stack

        const float PI = acos(-1);
        float sectorStep = 2 * PI / sectorCount;
        float sectorAngle;  // radian

        // compute the normal vector at 0 degree first
        // tanA = (baseRadius-topRadius) / height
        float zAngle = atan2(baseRadius - topRadius, height);
        float x0 = cos(zAngle);     // nx
        float y0 = 0;               // ny
        float z0 = sin(zAngle);     // nz

        // rotate (x0,y0,z0) per sector angle
        std::vector<float> sideNormals;
        for (int i = 0; i <= sectorCount; ++i)
        {
            sectorAngle = i * sectorStep;
            sideNormals.push_back(cos(sectorAngle) * x0 - sin(sectorAngle) * y0);   // nx
            sideNormals.push_back(sin(sectorAngle) * x0 + cos(sectorAngle) * y0);   // ny
            sideNormals.push_back(z0);  // nz
        }

        std::vector<float> unitCircleVertices;
        for (int i = 0; i <= sectorCount; ++i)
        {
            sectorAngle = i * sectorStep;
            unitCircleVertices.push_back(cos(sectorAngle)); // x
            unitCircleVertices.push_back(sin(sectorAngle)); // y
            unitCircleVertices.push_back(0);                // z
        }

        // remember where the base.top vertices start
        unsigned int baseVertexIndex = (unsigned int)vertices.size();
        // TODO: Convert this
        // put vertices of base of cylinder
        z = -height * 0.5f;
        //normals.push_back(glm::vec3(0, 0, -1));
        vertices.push_back(VertexData3D(maths::vec3(0, 0, z), maths::vec2(0.5f, 0.5f), 0, m_Color));
        for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
        {
            x = unitCircleVertices[j];
            y = unitCircleVertices[j + 1];
            //normals.push_back(glm::vec3(0, 0, -1));
            vertices.push_back(VertexData3D(maths::vec3(x * baseRadius, y * baseRadius, z), maths::vec2(-x * 0.5f + 0.5f, -y * 0.5f + 0.5f), 0, m_Color));

        }

        // remember where the top vertices start
        unsigned int topVertexIndex = (unsigned int)vertices.size();
        // put vertices of top of cylinder
        z = height * 0.5f;
        //normals.push_back(glm::vec3(0, 0, 1));
        vertices.push_back(VertexData3D(maths::vec3(0, 0, z), maths::vec2(0.5f, 0.5f), 0, m_Color));
        for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
        {
            x = unitCircleVertices[j];
            y = unitCircleVertices[j + 1];
            //normals.push_back(glm::vec3(0, 0, 1));
            vertices.push_back(VertexData3D(maths::vec3(x * topRadius, y * topRadius, z), maths::vec2(x * 0.5f + 0.5f, -y * 0.5f + 0.5f), 0, m_Color));
        }


        int k1 = 0;                         // 1st vertex index at base
        int k2 = sectorCount + 1;           // 1st vertex index at top

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if (j == 0)
            {
                // 2 triangles per sector
                indices.push_back(k1 + sectorCount);
                indices.push_back(k1 + 1);
                indices.push_back(k2 + sectorCount);

                indices.push_back(k2 + sectorCount);
                indices.push_back(k1 + 1);
                indices.push_back(k2 + 1);
            }
            else
            {
                // 2 triangles per sector
                indices.push_back(k1);
                indices.push_back(k1 + 1);
                indices.push_back(k2);

                indices.push_back(k2);
                indices.push_back(k1 + 1);
                indices.push_back(k2 + 1);
            }
        }

        // put indices for base
        for (int i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k)
        {
            if (i < (sectorCount - 1))
            {
                indices.push_back(baseVertexIndex);
                indices.push_back(k + 1);
                indices.push_back(k);
            }
            else    // last triangle
            {
                indices.push_back(baseVertexIndex);
                indices.push_back(baseVertexIndex + 1);
                indices.push_back(k);
            }
        }

        // put indices for top
        for (int i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
        {
            if (i < (sectorCount - 1))
            {
                indices.push_back(topVertexIndex);
                indices.push_back(k);
                indices.push_back(k + 1);
            }
            else
            {
                indices.push_back(topVertexIndex);
                indices.push_back(k);
                indices.push_back(topVertexIndex + 1);
            }
        }

        m_Vertices.insert(m_Vertices.begin(), vertices.begin(), vertices.end());
        m_Indices.insert(m_Indices.begin(), indices.begin(), indices.end());
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

} }
