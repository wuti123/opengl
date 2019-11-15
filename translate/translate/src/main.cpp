// ʹ����ɫ����Ĵ���
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader.h" // ��main.cpp�����ļ��п�ʼ����

#include <iostream>


void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float mixValue = 0.2f;   // ��������Ļ�ϱ���


//int main(int argc, char** argv)
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ������ɫ�������
	Shader ourShader("src/translate.vs", "src/translate.fs");  // �ӹ����ļ�Ŀ¼��λ�ÿ�ʼ����

	float vertices[] = {
	// λ��                    // ��ɫ              // ��������
		0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 
		0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 
	   -0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
	   -0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 
	};
	unsigned int indices[] = {
		0, 1, 3,  // ��һ��������
		1, 2, 3   // �ڶ���������
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// ��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);


	// ���ز�������һ������opengl��֤������16������Ԫ�ɹ�ʹ�ã�
	unsigned int texture1;   // ���Ҫ���ض��������������Ϊ����
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // ��С����ʱ���˷�ʽ
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // �Ŵ����ʱ���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// ��������ͼƬ���������������
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // ����stb_image.h��y���Ϸ�ת���ص�����,������ص���������ͼƬ������ת
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// ������glTexImage2Dʱ����ǰ�󶨵��������ͻᱻ����������ͼ��
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);   // ���ɶ༶��Զ����
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// �������������Ӧ�Ķ༶��Զ������ͷ�ͼ����ڴ�
	stbi_image_free(data);


	// ���ز������ڶ�������
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Ϊ��ǰ�󶨵ĵڶ�������������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// ��������ͼƬ���������������
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// awesomeface.png����͸���ȣ������alphaͨ��������һ��Ҫ����OpenGL����������GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	// �����
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	// ����openglÿ�������������ĸ�����Ԫ(ֻ��Ҫ��һ��)
	ourShader.use();  // ������uniform֮ǰ����Ҫ���Ǽ���/ʹ����ɫ��
	//glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture1"), 0);
	ourShader.setInt("ourTexture1", 0);
	ourShader.setInt("ourTexture2", 1);



	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.setFloat("mixValue", mixValue);  // ѭ��ǰ������use()�����Կ�������uniform

		glActiveTexture(GL_TEXTURE0);  // �ڰ�����֮ǰ�ȼ�������Ԫ,ֻ��һ������ʱ,���Բ����ֶ����Ĭ�ϼ���
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ����4x4��λ����Ȼ��ƽ�Ʊ任������ת�任�������ű任������붥��λ���������
		// �����⼸�����������д���������Է���ʵ�����������ž�����������ˣ���˽��������ת������ˣ��������ƽ�ƾ�����ˣ�
		// �Ƚ������Ų�����Ȼ������ת��������λ��
		glm::mat4 trans = glm::mat4(1.0f);  // ����һ��4x4��λ����
		// ������ƽ�Ƶ���Ļ���½�
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		// ��������z����ת
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		/*std::cout << glfwGetTime() << std::endl;*/
		// �Ѿ�����ÿ���ᶼ���ŵ�0.5��
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		// ��VAO��������,�����Զ�������ֵ��Ƭ����ɫ���Ĳ�����
		glBindVertexArray(VAO);   // ǰ�沢û�а�VAO��󶨣���ʵ���ﲻ���°�Ҳ�ǿ��Եģ����ж��VAO����Ҫ��
		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // ������������������ɣ�����6������,����һ������

		// �ڶ�������
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		// ��������z����ת
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		float scaleAmount = sin(glfwGetTime());
		trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);

		/*glDrawArrays(GL_TRIANGLES, 0, 3);*/
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // ������������������ɣ�����6�����㣬���ڶ�������

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();


	return 0;
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);  // �ӿ�
}


// ������������:��ѯGLFW�Ƿ���/�ͷ��˴�֡����ؼ�����������Ӧ�ķ�Ӧ
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // ����esc
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)     // ����up
	{
		mixValue += 0.01f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  // ����down
	{
		mixValue -= 0.01f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}



