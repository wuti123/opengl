/*
	Ҫ��ס��glad.c�ļ���ӵ�������
*/


#include "glad/glad.h"
#include <glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
	glViewport(0, 0, width, height);
}


// ������ɫ��Դ���ַ���
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Ƭ����ɫ��Դ���ַ���
const char* fragmentShaderSOURCE = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


int main()
{
	// ��GLFW��ʼ������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();  // // �ͷ�/ɾ��֮ǰ�����������Դ
		return -1;
	}

	// �˺���ʹ�����߳���ָ�����ڵ�OpenGL��OpenGL ES�����Ĵ��ڵ�ǰ״̬
	glfwMakeContextCurrent(window);

	// ��ʼ��GLAD
	// �����ʼ��GLAD����Ȼ�޷����ú���������ɫ�������VBO����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// ����OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ����������ɫ��������
	unsigned int vertexShader = 0;  // ��ID������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);    // ����һ��������ɫ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);  // �Ѷ�����ɫ��Դ�븽�ӵ�������ɫ��������
	glCompileShader(vertexShader);                      // ���붥����ɫ��
	
	// ��ⶥ����ɫ���Ƿ����ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ����Ƭ����ɫ��������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSOURCE, NULL);  // ��Ƭ����ɫ��Դ�븽�ӵ�Ƭ����ɫ��������
	glCompileShader(fragmentShader);

	// ���Ƭ����ɫ���Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// ������ɫ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// ����ɫ�����ӵ������ϣ�Ȼ����glLinkProgram����
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// ���������ɫ�������Ƿ�ʧ�ܣ�����ȡ��Ӧ����־��
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
	}

	// ����ɫ���������ӵ��������֮��ɾ����ɫ���������ǲ�����Ҫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// �������㻺�����VBO�������������VAO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);       // ʹ��glGenBuffers������һ������ID����һ��VBO����
	// ���ƶ������鵽�����й�OpenGLʹ��
	glBindVertexArray(VAO);  // ��VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��VBO�����㻺�����Ļ���������GL_ARRAY_BUFFER, ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	// ����Ķ���3D����
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, -0.7f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // ���û���������ݸ��Ƶ���ǰ�󶨻���

	// ����OpenGL����ν�����������,�Ѷ����������ӵ�������ɫ���Ķ��������ϣ������Ӷ�������
	// ÿ���������Դ�һ��VBO������ڴ��л���������ݣ��������Ǵ��ĸ�VBO�������п����ж��VBO����ȡ����ͨ���ڵ���glVertexAttribPointerʱ�󶨵�GL_ARRAY_BUFFER��VBO�����ġ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);      // ���ö�������

	// �����
	glBindBuffer(GL_ARRAY_BUFFER, 0);  // ���VBO�İ�
	glBindVertexArray(0);              // ���VAO�İ�


	// ����
	float vertices1[] = {
	0.5f, 0.5f, 0.0f,     // ���Ͻ�
	0.5f, -0.5f, 0.0f,    // ���½�
	-0.5f, -0.5f, 0.0f,   // ���½�
	-0.5f, 0.5f, 0.0f     // ���Ͻ�
	};
	unsigned int indices[] = {  // ������0��ʼ
		0, 1, 3,              // ��һ��������
		1, 2, 3               // �ڶ���������
	};
	unsigned int VBO1, VAO1, EBO;
	glGenVertexArrays(1, &VAO1);   // ���������������
	glGenBuffers(1, &VBO1);        // �������㻺�����
	glGenBuffers(1, &EBO);        // ���������������

	glBindVertexArray(VAO1);       // ���ȣ��󶨶����������

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);   // �󶨶����������֮���ٰ󶨶��㻺�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);   // ��6���������ݸ��Ƶ�����

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);   // �ڰ�VAO֮���VBO, ��VBO֮���ٰ�EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);   // ���������Ƶ�����

	// ���Ӷ�������
	// ÿ���������Դ�һ��VBO������ڴ��л���������ݣ��������Ǵ��ĸ�VBO�������п����ж��VBO����ȡ����ͨ���ڵ���glVertexAttribPointerʱ�󶨵�GL_ARRAY_BUFFER��VBO�����ġ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);            // ���ö������ԣ���������Ĭ���ǽ��õ�

	// ע�⣬��������ģ�����glVertexAttribPointer��VBOע��Ϊ�������Եİ󶨶��㻺��������
	// �������ǾͿ��԰�ȫ�ؽ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ��ס:��VAO���ڻ״̬ʱ����Ҫ���EBO����Ϊ�󶨵�Ԫ�ػ���������洢��VAO��;������Σ�����EBO���ڰ�״̬��
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ��������֮����VAO������������VAO���þͲ���������޸����VAO����������������ٷ�����
	// ������Σ��޸�����VAOs����Ҫ����glBindVertexArray�����Ե���ֱ����Ҫʱ������ͨ��������VAOs(��VBOs)��
	glBindVertexArray(0);

	// �������߿�ģʽ����ͼ��(�������ģʽ)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		//// ������ɫ���������
		//glUseProgram(shaderProgram);
		//// ����ǰ�����úõ�VAO
		//glBindVertexArray(VAO);
		//// ����������
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// ������ɫ���������
		glUseProgram(shaderProgram);
		// ����ǰ�����úõ�VAO
		glBindVertexArray(VAO1);
		// ���ƾ���
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);  // ������ɫ����
		glfwPollEvents();         // �����û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
	}

	glfwTerminate();
	
	return 0;
}
