//// ʹ����ɫ����Ĵ���
//#define STB_IMAGE_IMPLEMENTATION
//#include <glad/glad.h>
//#include <glfw3.h>
//#include <stb_image.h>   // ���������
//
//// glm
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "../include/shader.h" // ��main.cpp�����ļ��п�ʼ����
//
//#include <iostream>
//
//
//void framebuffer_size_callback(GLFWwindow * window, int width, int height);  // ע���ӿ�
//void processInput(GLFWwindow* window);                                       // ��������Ӧ����
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);           // ��갴���Ļص�����
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);    // �����ֻص�����
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//float mixValue = 0.2f;   // ��������Ļ�ϱ���
//
//float view_z = 0.0f;  // �����۲����ǰ���ƶ�����
//float view_x = 0.0f;  // �����۲���������ƶ�
//float view_y = 0.0f;  // �����۲���������ƶ�
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);    // ���λ��
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); // 
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // ������
//
//float deltaTime = 0.0f;      // ��ǰ֡����һ֡��ʱ���
//float lastFrame = 0.0f;      // ��һ֡��ʱ��
//
//bool firstMouse = true;      // ����״ν��봰�ڱ�־λ
//float lastX = 800.0f / 2.0;  // ����ڴ��ڵĵ�x���꣬��ʼֵΪ���ڵ����ĵ�
//float lastY = 600.0f / 2.0;  // ����ڴ��ڵĵ�y���꣬��ʼֵΪ���ڵ����ĵ�
//float yaw = -90.0f;          // ƫ���ǣ��������ҵĽǶ�
//float pitch = 0.0f;          // �����ǣ��������µĽǶ�
//
//float fov = 45.0f;           // �������Ұ��Χ
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", nullptr, nullptr);
//
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // ע���ӿ�
//	glfwSetCursorPosCallback(window, mouse_callback);  // ע����갴���Ļص�����
//	glfwSetScrollCallback(window, scroll_callback);    // ע�������ֵĻص�����
//
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // ���������ͣ���ڴ����в�����
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// ����ȫ��opengl״̬��������Ȳ���
//	glEnable(GL_DEPTH_TEST);
//
//	// ������ɫ�������
//	Shader ourShader("src/coord_system.vs", "src/coord_system.fs");  // �ӹ����ļ�Ŀ¼��λ�ÿ�ʼ����
//
//	//float vertices[] = {
//	//// λ��                    // ��ɫ              // ��������
//	//	0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 
//	//	0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 
//	//   -0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
//	//   -0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 
//	//};
//
//	//unsigned int indices[] = {
//	//0, 1, 3,  // ��һ��������
//	//1, 2, 3   // �ڶ���������
//	//};
//
//	// �ֲ��ռ�����
//	float vertices[] = {
//		// λ��               // ����
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	unsigned int VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// λ������
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//// ��ɫ����
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
//	//glEnableVertexAttribArray(1);
//
//	// ��������
//	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
//	//glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//
//	// ���ز�������һ������opengl��֤������16������Ԫ�ɹ�ʹ�ã�
//	unsigned int texture1;   // ���Ҫ���ض��������������Ϊ����
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // ��С����ʱ���˷�ʽ
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // �Ŵ����ʱ���˷�ʽ
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	// ��������ͼƬ���������������
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // ����stb_image.h��y���Ϸ�ת���ص�����,������ص���������ͼƬ������ת
//	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// ������glTexImage2Dʱ����ǰ�󶨵��������ͻᱻ����������ͼ��
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);   // ���ɶ༶��Զ����
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	// �������������Ӧ�Ķ༶��Զ������ͷ�ͼ����ڴ�
//	stbi_image_free(data);
//
//
//	// ���ز������ڶ�������
//	unsigned int texture2;
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	// Ϊ��ǰ�󶨵ĵڶ�������������û��ơ����˷�ʽ
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	// ��������ͼƬ���������������
//	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// awesomeface.png����͸���ȣ������alphaͨ��������һ��Ҫ����OpenGL����������GL_RGBA
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//
//	// �����
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//
//	ourShader.use();  // ������uniform֮ǰ����Ҫ���Ǽ���/ʹ����ɫ��
//	// ����openglÿ�������������ĸ�����Ԫ(ֻ��Ҫ��һ��)
//	ourShader.setInt("ourTexture1", 0);
//	ourShader.setInt("ourTexture2", 1);
//
//	glm::vec3 cubePositions[] = {
//		glm::vec3( 0.0f,  0.0f,  0.0f),
//		glm::vec3( 2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3( 2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -5.5f),
//		glm::vec3( 1.3f, -2.0f, -2.5f),
//		glm::vec3( 1.5f,  2.0f, -2.5f),
//		glm::vec3( 1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//
//	while (!glfwWindowShouldClose(window))
//	{
//		// ������Ⱦ��һ֡���õ�ʱ��
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		//glClear(GL_COLOR_BUFFER_BIT);  // ������ɫ����
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // ������ɫ�������Ȼ���
//
//
//		ourShader.setFloat("mixValue", mixValue);  // ѭ��ǰ������use()�����Կ�������uniform
//
//		glActiveTexture(GL_TEXTURE0);              // �ڰ�����֮ǰ�ȼ�������Ԫ,ֻ��һ������ʱ,���Բ����ֶ����Ĭ�ϼ���
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		glm::mat4 view = glm::mat4(1.0f);         // ��ʼ���۲����Ϊ4x4��λ����
//		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);  
//		//view = glm::lookAt(cameraPos, cameraFront, cameraUp);
//
//		glm::mat4 projection = glm::mat4(1.0f);   // ��ʼ��ͶӰ����
//		//projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
//		projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
//
//		//int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
//		int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
//
//		// ����uniform����֮ǰ�����ȼ�����ɫ���������
//		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
//
//		// ��VAO��������,�����Զ�������ֵ��Ƭ����ɫ���Ĳ�����
//		glBindVertexArray(VAO);   // ǰ�沢û�а�VAO��󶨣���ʵ���ﲻ���°�Ҳ�ǿ��Եģ����ж��VAO����Ҫ��
//		//glDrawArrays(GL_TRIANGLES, 0, 3);   // �Ӷ�����������н��л���
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // ������������������ɣ�����6������,����һ������,��ʹ�õ�ǰ�󶨵�������������е��������л���
//		// ѭ���ı�10��ģ�;��󣬲���10������
//		for (unsigned int i = 0; i < 10; ++i)
//		{
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * (i+1);
//			//if (i % 3 == 0)
//				//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));  // ��z����ת
//			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			ourShader.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//
//
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//
//	return 0;
//}
//
//
//void framebuffer_size_callback(GLFWwindow * window, int width, int height)
//{
//	glViewport(0, 0, width, height);  // �ӿ�
//}
//
//
//// ������������:��ѯGLFW�Ƿ���/�ͷ��˴�֡����ؼ�����������Ӧ�ķ�Ӧ
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // ����esc
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)     // ����up
//	{
//		mixValue += 0.01f;
//		if (mixValue >= 1.0f)
//			mixValue = 1.0f;
//
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  // ����down
//	{
//		mixValue -= 0.01f;
//		if (mixValue <= 0.0f)
//			mixValue = 0.0f;
//	}
//
//	float cameraSpeed = 2.5f * deltaTime;                 // ͨ��ʱ���ƽ�ⲻͬӲ�����ƶ��ٶ�
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		std::cout << "deltaTime = " << cameraSpeed << std::endl;
//		cameraPos += cameraSpeed * cameraFront;
//	}	
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;   // cross()��ʾ�������
//		//cameraPos -= glm::normalize(glm::cross(cameraPos, (cameraPos - cameraFront))) * cameraSpeed;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}
//
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	std::cout << "xpos: " << xpos << std::endl;
//	std::cout << "ypos: " << ypos << std::endl;
//
//	// ��ȡ����������һ֡λ�õ�ƫ����
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;  // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
//	lastX = xpos;
//	lastY = ypos;
//
//	// ����������
//	float sensitivity = 0.1f;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	// �޶������ǵķ�Χ
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	// ���ڸ����Ǻ�ƫ���ǵķ�������
//	glm::vec3 front;
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//
//	cameraFront = glm::normalize(front);   // ��һ��
//}
//
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	if (fov >= 1.0f && fov <= 90.0f)
//		fov -= yoffset;
//	if (fov <= 1.0f)
//		fov = 1.0f;
//	if (fov >= 90.0f)
//		fov = 90.0f;
//}



#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/camera.h"
#include "../include/shader.h"

#include <iostream>

#include <opencv.hpp>

using namespace cv;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);   // �����ӿڻص�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos);           // ���λ�ûص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);    // �����ֻص�����
void processInput(GLFWwindow* window);                                       // ���ڰ�����Ӧ�ص�����

// ���ڴ�С
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

// �������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // ����camera����
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// ��¼ʱ��
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// �����ϱ���
float mixValue = 0.2f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "learnOpenGL", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// ����GLFWץס���ǵ����(����������ڴ����У�������)
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);

	Shader ourShader("src/coord_system.vs", "src/coord_system.fs");

	float vertices[] = {
	// λ��               // ����
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// 10�������������ռ�λ��
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture[2];
	glGenTextures(2, texture);
	// ����1
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// ���������ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // ����stb_image.h��y���Ϸ�ת���ص�����

	cv::Mat tmp_img = cv::imread("container.jpg");
	cv::imshow("1", tmp_img);
	width = tmp_img.cols;
	height = tmp_img.rows;
	nrChannels = tmp_img.channels();

	//unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (tmp_img.data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, tmp_img.data);    // opencvĬ������BGR�洢��
		glGenerateMipmap(GL_TEXTURE_2D);    // ���ɶ༶��������
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);   // �ͷ�ͼƬ����

	// ����2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	//std::cout << "nrChannels: " << nrChannels << std::endl;
	tmp_img = cv::imread("awesomeface.png", -1);   // ��opencv����pngͼƬ
	if (tmp_img.data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);  // PNG��RGBA�洢
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, tmp_img.data);  // opencv��PNG��BGRA�洢
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);

	// ����openglÿ�������������ĸ�����Ԫ(ֻ��Ҫ��һ��)
	ourShader.use();  // ������ɫ������,����uniformʱ�����ȼ�����ɫ���������
	ourShader.setInt("ourTexture1", 0);
	ourShader.setInt("ourTexture2", 1);


	while (!glfwWindowShouldClose(window))
	{
		// ����ÿ֡��Ⱦʱ��
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// ��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ������󶨵���Ӧ������Ԫ��,������������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		//ourShader.use();

		ourShader.setFloat("mixValue", mixValue);

		// ��ͶӰ���󴫵ݸ���ɫ��(ע�⣬�����Ըı�ÿһ֡)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// �۲���󣨽���������ϵת�����۲�ռ䣬���������ϵ��
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		// ����ģ�;��󲢻��10��������
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);  // ȷ����ʼ��Ϊ��λ�������µ�glm�汾��Ĭ�ϳ�ʼ��Ϊ0����
			// �任�������š�����ת�����λ�Ƶ�˳��(��Ϊλ�ƾ���x��ת����x���ž���x���任����)
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i+1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// glfw:��������������ѯIO�¼�(����/�ͷż����ƶ�����)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// ��ֹ�����������ǰ�����GLFW��Դ
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;  // �ߵ��ˣ���Ϊy������µ���
	
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		mixValue += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		mixValue -= 0.01f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}