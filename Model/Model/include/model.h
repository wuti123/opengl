#pragma once
#include "mesh.h"
#include "shader.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// 加载纹理并返回纹理ID
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);


class Model
{
public:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	Model(string const &path, bool gamma = false);

	void Draw(Shader shader);

private:
	// 从文件中加载支持ASSIMP扩展的模型，并将结果网格存储在网格向量中
	void loadModel(string const &path);

	// 以递归方式处理节点，处理位于节点上的每个网格，并在其子节点（如果有）上重复此过程
	void processNode(aiNode *node, const aiScene *scene);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);


};
