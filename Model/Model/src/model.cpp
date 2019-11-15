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


// ���ļ��м���֧��ASSIMP��չ��ģ�ͣ������������洢������������
void Model::loadModel(string const &path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// ����filepath��Ŀ¼·��
	directory = path.substr(0, path.find_last_of('/'));

	// �ݹ鴦��ASSIMP�ĸ��ڵ�
	processNode(scene->mRootNode, scene);

}


// �Եݹ鷽ʽ����ڵ㣬����λ�ڽڵ��ϵ�ÿ�����񣬲������ӽڵ㣨����У����ظ��˹���
void Model::processNode(aiNode *node, const aiScene *scene)
{
	// ����λ�ڵ�ǰ�ڵ��ÿ������
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		// �ڵ����ֻ�������������������е�ʵ�ʶ���
		// �������������е����ݣ��ڵ�ֻ��������֯������
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// ���������е�����֮�󣬵ݹ鴦��ÿ���ӽڵ�
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}

}


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	// �������
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// ���������ÿ������
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		// ����һ��ռλ����������Ϊassimpʹ�����Լ��������࣬����������಻ֱ��ת��Ϊglm��vec3�࣬�������Ƚ����ݴ��ݸ����ռλ��
		glm::vec3 vector;
		// ����λ��
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// ���㷨��
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// ��������
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			// һ��������԰���8����ͬ���������꣬���費��ʹ��һ����������ж�����������ģ�ͣ�������ȡ��һ������0
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		// ����
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Normal = vector;
		// ˫����
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// ͨ�������ÿ���棨һ������һ������������Σ�������Ӧ�Ķ�������
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		// �������е��沢�洢������������
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	// ׼������
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	
	// ������ɫ���еĲ�����������һ��Լ����ÿ������������Ӧ������Ϊ��texture_diffuseN��
	// ��������Ҳ����ˣ����淴�䣺texture_specularN; ���ߣ�texture_normalN
	// 1.��������ͼ
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2.���淴����ͼ
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3.������ͼ
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4.height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");

	// ���ش���ȡ���������ݴ������������
	return Mesh(vertices, indices, textures);
}


vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// ��������Ƿ���֮ǰ���أ�����ǣ��������һ����������������һ���µ�����
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
			// �������û�м��أ�������
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



// ����������������ID
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