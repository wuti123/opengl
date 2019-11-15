#include "../include/model.h"



Model::Model(string const &path, bool gamma)
{
	loadModel(path);
}



void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); ++i)
		meshes[i].Draw(shader);
}


// 从文件中加载支持ASSIMP扩展的模型，并将结果网格存储在网格向量中
void Model::loadModel(string const &path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// 检索filepath的目录路径
	directory = path.substr(0, path.find_last_of('/'));

	// 递归处理ASSIMP的根节点
	processNode(scene->mRootNode, scene);

}


// 以递归方式处理节点，处理位于节点上的每个网格，并在其子节点（如果有）上重复此过程
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// 处理位于当前节点的每个网络
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		// 节点对象只包含索引来索引场景中的实际对象
		// 场景包含了所有的数据，节点只是用来组织东西的
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// 处理完所有的网格之后，递归处理每个子节点
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}

}


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	// 数据填充
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// 遍历网格的每个顶点
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		// 声明一个占位符向量，因为assimp使用它自己的向量类，二这个向量类不直接转换为glm的vec3类，所以首先将数据传递给这个占位符
		glm::vec3 vector;
		// 顶点位置
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// 顶点法线
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// 纹理坐标
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			// 一个顶点可以包含8个不同的纹理坐标，假设不会使用一个顶点可以有多个纹理坐标的模型，故总是取第一个集合0
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		// 切线
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Normal = vector;
		// 双切线
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// 通过网格的每个面（一个面是一个网格的三角形）检索相应的顶点索引
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		// 检索所有的面并存储在索引向量中
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	// 准备材料
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	
	// 假设着色器中的采样器名称有一个约定，每个漫反射纹理应该命名为“texture_diffuseN”
	// 其它纹理也是如此：镜面反射：texture_specularN; 法线：texture_normalN
	// 1.漫反射贴图
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2.镜面反射贴图
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3.法线贴图
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4.height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

	// 返回从提取的网络数据创建的网格对象
	return Mesh(vertices, indices, textures);
}


vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// 检查纹理是否在之前加载，如果是，则继续下一个迭代，跳过加载一个新的纹理
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); ++j)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			// 如果纹理还没有加载，加载它
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;

}



// 加载纹理并返回纹理ID
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		unsigned int format;
		if (1 == nrComponents)
			format = GL_RED;
		else if (3 == nrComponents)
			format = GL_RGB;
		else if (4 == nrComponents)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}