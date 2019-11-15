//// 使用着色器类的代码
//#define STB_IMAGE_IMPLEMENTATION
//#include <glad/glad.h>
//#include <glfw3.h>
//#include <stb_image.h>   // 加载纹理库
//
//// glm
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "../include/shader.h" // 从main.cpp所在文件夹开始检索
//
//#include <iostream>
//
//
//void framebuffer_size_callback(GLFWwindow * window, int width, int height);  // 注册视口
//void processInput(GLFWwindow* window);                                       // 按键的响应函数
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);           // 鼠标按键的回调函数
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);    // 鼠标滚轮回调函数
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//float mixValue = 0.2f;   // 两张纹理的混合比例
//
//float view_z = 0.0f;  // 调整观察矩阵前后移动距离
//float view_x = 0.0f;  // 调整观察矩阵左右移动
//float view_y = 0.0f;  // 调整观察矩阵上下移动
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);    // 相机位置
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); // 
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // 上向量
//
//float deltaTime = 0.0f;      // 当前帧与上一帧的时间差
//float lastFrame = 0.0f;      // 上一帧的时间
//
//bool firstMouse = true;      // 鼠标首次进入窗口标志位
//float lastX = 800.0f / 2.0;  // 鼠标在窗口的的x坐标，初始值为窗口的中心点
//float lastY = 600.0f / 2.0;  // 鼠标在窗口的的y坐标，初始值为窗口的中心点
//float yaw = -90.0f;          // 偏航角，向左向右的角度
//float pitch = 0.0f;          // 俯仰角，向上向下的角度
//
//float fov = 45.0f;           // 摄像机视野范围
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
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // 注册视口
//	glfwSetCursorPosCallback(window, mouse_callback);  // 注册鼠标按键的回调函数
//	glfwSetScrollCallback(window, scroll_callback);    // 注册鼠标滚轮的回调函数
//
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // 设置鼠标光标停留在串口中并隐藏
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// 配置全局opengl状态，启用深度测试
//	glEnable(GL_DEPTH_TEST);
//
//	// 创建着色器类对象
//	Shader ourShader("src/coord_system.vs", "src/coord_system.fs");  // 从工程文件目录的位置开始检索
//
//	//float vertices[] = {
//	//// 位置                    // 颜色              // 纹理坐标
//	//	0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 
//	//	0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 
//	//   -0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
//	//   -0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 
//	//};
//
//	//unsigned int indices[] = {
//	//0, 1, 3,  // 第一个三角形
//	//1, 2, 3   // 第二个三角形
//	//};
//
//	// 局部空间坐标
//	float vertices[] = {
//		// 位置               // 纹理
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
//	// 位置属性
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//// 颜色属性
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
//	//glEnableVertexAttribArray(1);
//
//	// 纹理坐标
//	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
//	//glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//
//	// 加载并创建第一个纹理（opengl保证至少有16个纹理单元可供使用）
//	unsigned int texture1;   // 如果要加载多个纹理，这里设置为数组
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	// 为当前绑定的纹理对象设置环绕、过滤方式
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 缩小操作时过滤方式
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 放大操作时过滤方式
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	// 加载纹理图片并附到纹理对象上
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true); // 告诉stb_image.h在y轴上翻转加载的纹理,后面加载的所有纹理图片都将翻转
//	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// 当调用glTexImage2D时，当前绑定的纹理对象就会被附加上纹理图像
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);   // 生成多级渐远纹理
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	// 生成了纹理和相应的多级渐远纹理后，释放图像的内存
//	stbi_image_free(data);
//
//
//	// 加载并创建第二个纹理
//	unsigned int texture2;
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	// 为当前绑定的第二个纹理对象设置环绕、过滤方式
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	// 加载纹理图片并附到纹理对象上
//	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		// awesomeface.png具有透明度，因此是alpha通道，所以一定要告诉OpenGL数据类型是GL_RGBA
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
//	// 解除绑定
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//
//	ourShader.use();  // 在设置uniform之前，不要忘记激活/使用着色器
//	// 告诉opengl每个采样器属于哪个纹理单元(只需要做一次)
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
//		// 计算渲染上一帧所用的时间
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		//glClear(GL_COLOR_BUFFER_BIT);  // 清理颜色缓冲
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清理颜色缓冲和深度缓冲
//
//
//		ourShader.setFloat("mixValue", mixValue);  // 循环前调用了use()，所以可以设置uniform
//
//		glActiveTexture(GL_TEXTURE0);              // 在绑定纹理之前先激活纹理单元,只有一个纹理时,可以不用手动激活，默认激活
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		glm::mat4 view = glm::mat4(1.0f);         // 初始化观察矩阵为4x4单位矩阵
//		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);  
//		//view = glm::lookAt(cameraPos, cameraFront, cameraUp);
//
//		glm::mat4 projection = glm::mat4(1.0f);   // 初始化投影矩阵
//		//projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
//		projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
//
//		//int modelLoc = glGetUniformLocation(ourShader.ID, "model");
//		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
//		int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
//
//		// 设置uniform变量之前必须先激活着色器程序对象
//		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
//		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
//
//		// 绑定VAO后会绑定纹理,它会自动把纹理赋值给片段着色器的采样器
//		glBindVertexArray(VAO);   // 前面并没有把VAO解绑定，其实这里不重新绑定也是可以的，但有多个VAO就需要绑定
//		//glDrawArrays(GL_TRIANGLES, 0, 3);   // 从顶点数组对象中进行绘制
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // 矩形由两个三角形组成，故是6个顶点,画第一个箱子,会使用当前绑定的索引缓冲对象中的索引进行绘制
//		// 循环改变10次模型矩阵，并绘10个箱子
//		for (unsigned int i = 0; i < 10; ++i)
//		{
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * (i+1);
//			//if (i % 3 == 0)
//				//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));  // 绕z轴旋转
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
//	glViewport(0, 0, width, height);  // 视口
//}
//
//
//// 处理所有输入:查询GLFW是否按下/释放了此帧的相关键，并做出相应的反应
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // 键盘esc
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)     // 键盘up
//	{
//		mixValue += 0.01f;
//		if (mixValue >= 1.0f)
//			mixValue = 1.0f;
//
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  // 键盘down
//	{
//		mixValue -= 0.01f;
//		if (mixValue <= 0.0f)
//			mixValue = 0.0f;
//	}
//
//	float cameraSpeed = 2.5f * deltaTime;                 // 通过时间差平衡不同硬件的移动速度
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		std::cout << "deltaTime = " << cameraSpeed << std::endl;
//		cameraPos += cameraSpeed * cameraFront;
//	}	
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		cameraPos -= cameraSpeed * cameraFront;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;   // cross()表示向量叉乘
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
//	// 获取鼠标相对于上一帧位置的偏移量
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;  // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
//	lastX = xpos;
//	lastY = ypos;
//
//	// 定义灵敏度
//	float sensitivity = 0.1f;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw += xoffset;
//	pitch += yoffset;
//
//	// 限定俯仰角的范围
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//
//	// 基于俯仰角和偏航角的方向向量
//	glm::vec3 front;
//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//	front.y = sin(glm::radians(pitch));
//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//
//	cameraFront = glm::normalize(front);   // 归一化
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


void framebuffer_size_callback(GLFWwindow* window, int width, int height);   // 设置视口回调函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);           // 鼠标位置回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);    // 鼠标滚轮回调函数
void processInput(GLFWwindow* window);                                       // 窗口按键响应回调函数

// 窗口大小
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

// 相机参数
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));  // 创建camera对象
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// 记录时间
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// 纹理混合比例
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

	// 告诉GLFW抓住我们的鼠标(将鼠标锁定在窗口中，并隐藏)
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 开启深度测试
	glEnable(GL_DEPTH_TEST);

	Shader ourShader("src/coord_system.vs", "src/coord_system.fs");

	float vertices[] = {
	// 位置               // 纹理
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

	// 10个立方体的世界空间位置
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

	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 纹理坐标属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture[2];
	glGenTextures(2, texture);
	// 纹理1
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// 设置纹理环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // 告诉stb_image.h在y轴上翻转加载的纹理。

	cv::Mat tmp_img = cv::imread("container.jpg");
	cv::imshow("1", tmp_img);
	width = tmp_img.cols;
	height = tmp_img.rows;
	nrChannels = tmp_img.channels();

	//unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (tmp_img.data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, tmp_img.data);    // opencv默认是以BGR存储的
		glGenerateMipmap(GL_TEXTURE_2D);    // 生成多级渐进纹理
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);   // 释放图片数据

	// 纹理2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	//std::cout << "nrChannels: " << nrChannels << std::endl;
	tmp_img = cv::imread("awesomeface.png", -1);   // 用opencv加载png图片
	if (tmp_img.data)
	{
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);  // PNG是RGBA存储
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, tmp_img.data);  // opencv中PNG是BGRA存储
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);

	// 告诉opengl每个采样器属于哪个纹理单元(只需要做一次)
	ourShader.use();  // 激活着色器程序,设置uniform时必须先激活着色器程序对象
	ourShader.setInt("ourTexture1", 0);
	ourShader.setInt("ourTexture2", 1);


	while (!glfwWindowShouldClose(window))
	{
		// 计算每帧渲染时间
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// 渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 将纹理绑定到相应的纹理单元上,供采样器采样
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		//ourShader.use();

		ourShader.setFloat("mixValue", mixValue);

		// 将投影矩阵传递给着色器(注意，它可以改变每一帧)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// 观察矩阵（将世界坐标系转换到观察空间，即相机坐标系）
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		// 创建模型矩阵并绘出10个立方体
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);  // 确保初始化为单位矩阵，最新的glm版本，默认初始化为0矩阵
			// 变换以先缩放、再旋转、最后位移的顺序(故为位移矩阵x旋转矩阵x缩放矩阵x待变换矩阵)
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i+1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// glfw:交换缓冲区和轮询IO事件(按下/释放键，移动鼠标等)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// 终止，清除所有以前分配的GLFW资源
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
	float yoffset = lastY - ypos;  // 颠倒了，因为y坐标从下到上
	
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