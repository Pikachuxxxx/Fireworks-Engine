#include "model.h"

namespace fireworks { namespace graphics {

    Model::Model(std::string path, Transform transform, Shader* shader) 
        : Renderable3D(), m_Transform(transform), m_Shader(shader)
    {
        this->loadModel(path);
        this->shader = shader;
    }

    Model::~Model()
    {
        //delete modelIBO;
    }

    void Model::submit(Renderer3D* renderer) const
    {
        // TODO: Make m_RootMesh Heap allocated
        renderer->submit(new Renderable3D(m_RootMesh));
    }

    void Model::flush(Renderer3D* renderer, IndexBuffer* ibo /*= nullptr*/) const
    {
        renderer->flush(ibo);
    }

    void Model::loadModel(std::string path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_CalcTangentSpace      |
            aiProcess_Triangulate           |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType           |
            aiProcess_FlipUVs);

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }

        this->m_Directory = path.substr(0, path.find_last_of('/')); // WTF! happened here?
        size_t lastindex = path.find_last_of(".");
        std::string rawname = path.substr(0, lastindex);
        std::cout << "Path is : " << rawname << std::endl;
        m_Directory = rawname;
        m_RootMesh = this->processNode(scene->mRootNode, scene);
    }

    Mesh Model::processNode(aiNode* node, const aiScene* scene)
    {
        for (GLuint i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            subMeshes.push_back(processMesh(mesh, scene));
        }
        for (GLuint i = 0; i < node->mNumChildren; i++)
        {
            this->processNode(node->mChildren[i], scene);
        }

        SubMesh masterSubMesh;
        for (int i = 0; i < subMeshes.size(); i++)
        {
            masterSubMesh.vertices.insert(masterSubMesh.vertices.begin(), subMeshes[i].vertices.begin(), subMeshes[i].vertices.end());
            masterSubMesh.indices.insert(masterSubMesh.indices.begin(), subMeshes[i].indices.begin(), subMeshes[i].indices.end());
            masterSubMesh.material_textures.insert(masterSubMesh.material_textures.begin(), subMeshes[i].material_textures.begin(), subMeshes[i].material_textures.end());
        }
        modelIBO = new IndexBuffer(&(masterSubMesh.indices[0]), masterSubMesh.indices.size() * sizeof(GLushort));
        return Mesh(masterSubMesh.vertices, masterSubMesh.indices, masterSubMesh.material_textures, m_Transform, m_Shader);
    }

    SubMesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        /* Mesh data to fill */
        SubMesh submesh;

        for (GLuint i = 0; i < mesh->mNumVertices; i++)
        {
            VertexData3D vertex;

            // Vertex positions
            vertex.vertex = maths::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

            // TODO: Add normals to VertexData3D struct
            //vertex.normal = maths::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            // UV Coordinates
            if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
            {
                /*
                 * A vertex can contain up to 8 different texture coordinates. We thus make
                 * the assumption that we won't use models where a vertex can have multiple
                 * texture coordinates so we always take the first set (0).
                 */
                vertex.uv = maths::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else
                vertex.uv = maths::vec2(0.0f, 0.0f);

            vertex.color = maths::vec4(1, 0, 1, 1);
            submesh.vertices.push_back(vertex);
        }
        // Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (GLuint i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // Retrieve all indices of the face and store them in the indices vector
            for (GLuint j = 0; j < face.mNumIndices; j++)
                submesh.indices.push_back(face.mIndices[j]);
        }

        // Process the materials
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            /*
             * We assume a convention for sampler names in the shaders. Each diffuse texture  should be named
             * as 'texture_diffuseN' where N is a sequential number ranging from 1 to  MAX_SAMPLER_NUMBER.
             * Same applies to other texture as the following list summarizes:
             * Diffuse  : texture_diffuseN
             * Specular : texture_specularN
             * Normal   : texture_normalN
            */

            std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            submesh.material_textures.insert(submesh.material_textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            submesh.material_textures.insert(submesh.material_textures.end(), specularMaps.begin(), specularMaps.end());
        }
        this->vertexCount += submesh.vertices.size();
        this->trisCount += submesh.indices.size() / 3;

        return submesh;
    }

    // TODO: typeName isn't used by the fireworks::graphics::Texture
    std::vector<fireworks::graphics::Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType texType, std::string typeName)
    {
        std::vector<Texture> textures;
        for (GLuint i = 0; i < material->GetTextureCount(texType); i++)
        {
            aiString str;
            material->GetTexture(texType, i, &str);
            std::cout << "Texture Path is : " << m_Directory + std::string("\\") + std::string( str.C_Str()) << std::endl;
            GLboolean skip = false;
            for (GLuint j = 0; j < m_LoadedTextures.size(); j++)
            {
                // Making sure we aren't loading duplicated textures, hence we check the path and cache the already loaded ones
                if (m_LoadedTextures[j].getPath().c_str() == str.C_Str())
                {
                    textures.push_back(m_LoadedTextures[j]);
                    skip = true;
                    break;
                }
                if (!skip)
                {
                    // If the texture hasn't been loaded, load it 
                    Texture tex(m_Directory + std::string("\\") + std::string(str.C_Str()), typeName);
                    textures.push_back(tex);
                    m_LoadedTextures.push_back(tex);
                }
            }
            return textures;
        }
    }

} }
