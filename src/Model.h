#pragma once
#include<iostream>
#include <glm.hpp>
#include<vector>
#include"Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;
unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

#define MAX_BONE_INFLUENCE 4
struct Vertex { //顶点结构体，包含了所需三个属性
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};
struct myTexture {//材质结构体
    unsigned int id;
    string type;
    aiString path;//存储材质路径，减少加载
};
class Mesh {
public:
    /*  网格数据  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<myTexture> textures;
    /*  函数  */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
    void Draw();
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    
    /*  函数  */
    void setupMesh();
};
class Model
{
public:
    

    /*  函数   */

    Model(char* path)
    {
        loadModel(path);
    }
    void Draw();
private:
    /*  模型数据  */
    //加载过的材质
    vector<myTexture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    
    /*  函数   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<myTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,string typeName);
};