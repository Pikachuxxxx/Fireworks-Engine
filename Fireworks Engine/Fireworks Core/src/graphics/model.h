#pragma once

#include "mesh.h"

// Assimp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace fireworks { namespace graphics {

    /// A struct denoting the sub-meshes of a 3d Model
    struct SubMesh
    {
        std::vector<VertexData3D> vertices;
        std::vector<GLushort> indices;
        std::vector<Texture> material_textures;
    };

    /// A 3D model object loaded externally 
    class Model : public Renderable3D
    {
    public:
        /// The vertex count of the 3d model
        GLuint                  vertexCount;
        /// The triangles count of the 3d model
        GLuint                  trisCount;
        /// Collections of sub-meshes that make up the 3d models
        std::vector<SubMesh>    subMeshes;
        /// The index buffer of the 3d model
        IndexBuffer*            modelIBO;
    private:
        Mesh                    m_RootMesh;
        std::string             m_Directory;
        std::vector<Texture>    m_LoadedTextures;
        Transform               m_Transform;
        Shader*                 m_Shader;
    public:
        /// Loads an external 3d model
        ///
        /// @param path The path of the 3d models
        /// @param transform The transform of the 3d model in 3D space
        /// @param shader The shader with which the 3d models is rendered with
        Model(std::string path, Transform transform, Shader* shader);
        ~Model();

        /// Returns the root mesh that is a congregation of all sub-meshes
        inline Mesh& getMasterMesh() { return m_RootMesh; }
    private:
        void submit(Renderer3D* renderer) const override;
        void loadModel(std::string path);
        Mesh processNode(aiNode* node, const aiScene* scene);
        SubMesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName);
    };
    
} }
