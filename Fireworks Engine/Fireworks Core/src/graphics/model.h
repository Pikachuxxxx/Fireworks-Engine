#pragma once

#include "mesh.h"

// Assimp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace fireworks { namespace graphics {

    struct SubMesh
    {
        std::vector<VertexData3D> vertices;
        std::vector<GLushort> indices;
        std::vector<Texture> material_textures;
    };

    class Model : public Renderable3D
    {
    public:
        GLuint vertexCount;
        GLuint trisCount;
        std::vector<SubMesh> subMeshes;
        IndexBuffer* modelIBO;
    private:
        Mesh                    m_RootMesh;
        std::string             m_Directory;
        std::vector<Texture>    m_LoadedTextures;
        Transform               m_Transform;
        Shader*                 m_Shader;
    public:
        Model(std::string path, Transform transform, Shader* shader);
        ~Model();

        inline Mesh& getMasterMesh() { return m_RootMesh; }
    private:
        void submit(Renderer3D* renderer) const override;
        void loadModel(std::string path);
        Mesh processNode(aiNode* node, const aiScene* scene);
        SubMesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName);
    };
    
} }
