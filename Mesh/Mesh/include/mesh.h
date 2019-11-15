#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include "shader.h"

#include <vector>
//#include <string.h>
using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;    // tangent
	glm::vec3 Bitangent;  // bitangent
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;    // ¶¥µãË÷Òý
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);


private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};


