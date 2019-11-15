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

// ����������������ID
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
	// ���ļ��м���֧��ASSIMP��չ��ģ�ͣ������������洢������������
	void loadModel(string const &path);

	// �Եݹ鷽ʽ����ڵ㣬����λ�ڽڵ��ϵ�ÿ�����񣬲������ӽڵ㣨����У����ظ��˹���
	void processNode(aiNode *node, const aiScene *scene);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);


};
