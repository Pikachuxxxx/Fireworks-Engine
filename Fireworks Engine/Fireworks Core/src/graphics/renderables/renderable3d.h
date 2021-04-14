#pragma once

#include <vector>
#include <iostream>

#include "../shader.h"
#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../buffers/vertexarray.h"
#include "../../maths/maths.h"
#include "../texture.h"
#include "../renderers/renderer3d.h"

namespace fireworks { namespace graphics {

    /// The vertex structure of a 3D primitive.
    struct VertexData3D
    {
        maths::vec3 vertex;
        // TODO: Use normals!
        //maths::vec3 normal;
        maths::vec2 uv;
        float       tid;
        maths::vec4 color;

        VertexData3D()
            : vertex(maths::vec3(0, 0, 0)), uv(maths::vec2(0, 0)), tid(0.0f), color(maths::vec4(1, 0, 1, 1))
        {

        }

        VertexData3D(maths::vec3 vertex, maths::vec2 uv, float texID, maths::vec4 color)
            : vertex(vertex), uv(uv), tid(texID), color(color)
        {
        }
    };

    /// The spacial orientation of an object in 3D space denoted by it's position, rotation and scale.
    struct Transform
    {
        maths::vec3 position;
        maths::vec3 rotation;
        maths::vec3 scale;

        Transform(maths::vec3 pos = maths::vec3(0, 0, 0), maths::vec3 rot = maths::vec3(0, 0, 0), maths::vec3 scale = maths::vec3(1, 1, 1))
            : position(pos), rotation(rot), scale(scale)
        {
        }
    };

    /// Different types of 3D renderable primitive objects.
    enum class Primitive3D
    {
        Plane,
        Cube,
        UVSphere,   /* UV sphere procedurally generated using rings count on the CPU side */
        Cylinder,  
        Torus,      /* UV Torus procedurally generated using preferences on the CPU side */
        None        /* If the primitive is none, then use the 3D Model for rendering the renderable*/
    };

    class Mesh;

    /// The Class responsible for drawing the basic 3D Renderable objects onto the screen.
    ///
    /// Every 3D renderable object is derived from this class
    class Renderable3D
    {
    public:
        /// The unique object ID of renderable object
        std::uint32_t                       objectID;
        /// The shader used to draw the renderable object 
        Shader*                             shader;
        /// The texture used to draw the renderable object
        Texture*                            m_Texture;
    protected:
        /// The transform of the object in 3D space
        Transform                           m_Transform;
        /// Vertex color of the renderable 
        maths::vec4                         m_Color;
        /// The basic primitive that is being rendered, (Does not denote the primitive used to render the 3d object)
        Primitive3D                         m_Primitive3D;
        /// The texture coordinates of the 3d renderable
        mutable std::vector<maths::vec2>    m_UV;
        /// The vertices pool of the 3d object
        std::vector<VertexData3D>           m_Vertices;
        /// The indices pool of the 3d object
        std::vector<GLushort>               m_Indices;
    private:
        static std::uint32_t                m_UniqueID;
    public:
        /// Creates the renderable. 
        /// 
        /// @param transform The Transform of the renderable
        /// @param color The color of the renderable
        /// @param primitive3d The primitive shape of the renderable
        /// @note This overload is to be used with graphics::BatchRenderer3D
        Renderable3D(Transform transform, maths::vec4 color, Primitive3D primitive3d)
            : m_Transform(transform), m_Color(color), m_Primitive3D(primitive3d), shader(nullptr), m_Texture(nullptr)
        {
            objectID = ++m_UniqueID;
            setUVDefaults();
        }

        /// Creates the renderable. 
        /// 
        /// @param transform The Transform of the renderable
        /// @param color The color of the renderable
        /// @primitive3d The primitive shape of the renderable
        /// @note This overload is to be used with graphics::ShotRenderer3D
        Renderable3D(Transform transform, maths::vec4 color, Primitive3D primitive3d, Shader* shader)
            : m_Transform(transform), m_Color(color), m_Primitive3D(primitive3d), shader(shader), m_Texture(nullptr)
        {
            objectID = ++m_UniqueID;
            setUVDefaults();
        }

        /// Creates the renderable. 
        /// 
        /// @param transform The Transform of the renderable
        /// @param color The color of the renderable
        /// @primitive3d The primitive shape of the renderable
        /// @note This overload is to be used with graphics::ShotRenderer3D
        Renderable3D(Transform transform, maths::vec4 color, Primitive3D primitive3d, Shader* shader, Texture* texture)
            : m_Transform(transform), m_Color(color), m_Primitive3D(primitive3d), shader(shader), m_Texture(texture)
        {
            objectID = ++m_UniqueID;
            shader->enable();
            GLint texIDs[] =
            {
                0, 1,  2,  3,  4,  5,  6,  7,
                8, 9, 10, 11, 12, 13, 14, 15
            };
            shader->setUniform1iv("textures", texIDs, 8);
            shader->disable();

            setUVDefaults();
        }

        /// Create a empty renderable.
        Renderable3D() : m_Texture(nullptr)
        {
            objectID = ++m_UniqueID;
        }

        virtual ~Renderable3D() { }

        /// Virtual overload of the submit function, customize the way you can submit the renderable to the renderer
        virtual void submit(Renderer3D* renderer) const
        {
            renderer->submit(this);
        }

        /// Gets the reference to the transform of the renderable object.
        inline const Transform& getTransform() const { return m_Transform; }
        /// Gets the reference to the color of the renderable object.
        inline const maths::vec4& getColor() const { return m_Color; }
        /// Gets the reference to the texture coordinates of the renderable.
        inline const std::vector<maths::vec2>& getUV() const { return m_UV; }
        /// Gets the texture ID of the texture being used by the renderable.
        inline const GLuint getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
        /// Gets the 3D primitive that is being rendered.
        inline const Primitive3D& gerPrimitive() const { return m_Primitive3D; }
        /// Gets vertices of the 3d renderable.
        inline std::vector<VertexData3D> getVerts() const { return m_Vertices; }
        /// Gets the vertices count of the 3d renderable.
        inline GLuint getVertsSize() const { return m_Vertices.size(); }
        /// Gets the indices of the 3d renderable
        inline std::vector<GLushort> getInidces() const { return m_Indices; }
        /// Gets the indices count of the 3d renderable
        inline GLsizei getIndicesSize() const { return m_Indices.size(); }
    private:
        void setUVDefaults()
        {
            int faces;
            if (m_Primitive3D == Primitive3D::Plane) /* Same as a Sprite */
            {
                faces = 1;
                // Iterating over each face
                for (int i = 0; i < faces; i++)
                {
                    m_UV.push_back(maths::vec2(0, 0));  // Bottom Left
                    m_UV.push_back(maths::vec2(0, 4));  // Top Left
                    m_UV.push_back(maths::vec2(4, 4));  // Top Right
                    m_UV.push_back(maths::vec2(4, 0));  // Bottom Right
                }
            }
            else if(m_Primitive3D == Primitive3D::Cube)
            {
                faces = 6;
                // Iterating over each face
                for (int i = 0; i < faces; i++)
                {
                    // Clockwise UV coordinates for each face
                    m_UV.push_back(maths::vec2(0, 0));  // Bottom Left
                    m_UV.push_back(maths::vec2(0, 1));  // Top Left
                    m_UV.push_back(maths::vec2(1, 1));  // Top Right
                    m_UV.push_back(maths::vec2(1, 0));  // Bottom Right
                }
            }
        }
    };

} }
