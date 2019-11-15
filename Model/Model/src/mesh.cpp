#include "../include/mesh.h"


// ���캯��
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices  = indices;
	this->textures = textures;

	setupMesh();
}

// ���ö�������
void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(struct Vertex), &vertices[0], GL_STATIC_DRAW);    // ������Ԫ�ظ�������ÿ��Ԫ����ռ�ֽ���

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// ����λ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)0);
	glEnableVertexAttribArray(0);

	// ���㷨��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, Normal));    // offsetof�ķ���ֵ�ǳ�Ա�ڸ����Ͷ����о��ṹ��ͷ�����ֽڼ����ƫ������offsetofֻ�����ͺͳ�Ա�йأ����ܴ���������
	glEnableVertexAttribArray(1);

	// ������������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, TexCoords)); // offsetof�ķ���ֵ�ǳ�Ա�ڸ����Ͷ����о��ṹ��ͷ�����ֽڼ����ƫ������offsetofֻ�����ͺͳ�Ա�йأ����ܴ���������
	glEnableVertexAttribArray(2);

	// ��������
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, Tangent));
	glEnableVertexAttribArray(3);

	// ����˫����
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void *)offsetof(struct Vertex, Bitangent));
	glEnableVertexAttribArray(4);


	glBindVertexArray(0);

}


// ����������������
void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;
	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);     // �ڰ�֮ǰ������Ӧ������Ԫ
		// ��ȡ�������(sampler2D diffuse_textureN�е�N)
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

		shader.setFloat(("material." + name + number).c_str(), i);     // �ַ�����Ӳ�ת����c����ַ���
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// ��������
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);	

	// һ�����úã���һ�����û�Ĭ��ֵ
	glActiveTexture(GL_TEXTURE0);
}
