#include "../include/mesh.h"


// 构造函数
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices  = indices;
	this->textures = textures;

	setupMesh();
}

// 设置顶点属性
void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(struct Vertex), &vertices[0], GL_STATIC_DRAW);    // 向量的元素个数乘以每个元素所占字节数

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// 顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)0);
	glEnableVertexAttribArray(0);

	// 顶点法线
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, Normal));    // offsetof的返回值是成员在该类型对象中距距结构体头部以字节计算的偏移量，offsetof只与类型和成员有关，不能传入具体对象
	glEnableVertexAttribArray(1);

	// 顶点纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, TexCoords)); // offsetof的返回值是成员在该类型对象中距距结构体头部以字节计算的偏移量，offsetof只与类型和成员有关，不能传入具体对象
	glEnableVertexAttribArray(2);

	// 顶点切线
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, Tangent));
	glEnableVertexAttribArray(3);

	// 顶点双切线
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, Bitangent));
	glEnableVertexAttribArray(4);


	glBindVertexArray(0);

}


// 绑定纹理，并绘制网格
void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;
	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);     // 在绑定之前激活相应的纹理单元
		// 获取纹理序号(sampler2D diffuse_textureN中的N)
		string number;
		string name = textures[i].type;
		if ("texture_diffuse" == name)
			number = std::to_string(diffuseNr++);
		else if ("texture_specular" == name)
			number = std::to_string(specularNr++);
		else if ("texture_normal" == name)
			number = std::to_string(normalNr++);
		else if ("texture_height" == name)
			number = std::to_string(heightNr++);

		shader.setFloat(("material." + name + number).c_str(), i);     // 字符串相加并转换成c风格字符串
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// 绘制网格
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);	

	// 一旦配置好，讲一切设置回默认值
	glActiveTexture(GL_TEXTURE0);
}
