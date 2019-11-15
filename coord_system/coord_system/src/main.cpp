// 使用着色器类的代码
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/shader.h" // 从main.cpp所在文件夹开始检索

#include <iostream>


void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float mixValue = 0.2f;   // 两张纹理的混合比例

float view_z = 0.0f;  // 调整观察矩阵前后移动距离
float view_x = 0.0f;  // 调整观察矩阵左右移动
float view_y = 0.0f;  // 调整观察矩阵上下移动

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

	// 配置全局opengl状态，启用深度测试
	glEnable(GL_DEPTH_TEST);

	// 创建着色器类对象
	Shader ourShader("src/coord_system.vs", "src/coord_system.fs");  // 从工程文件目录的位置开始检索

	//float vertices[] = {
	//// 位置                    // 颜色              // 纹理坐标
	//	0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 
	//	0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 
	//   -0.5f, -0.5f,  0.0f,   0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
	//   -0.5f,  0.5f,  0.0f,   1.0f, 1.0f, 0.0f,     0.0f, 1.0f, 
	//};

	//unsigned int indices[] = {
	//0, 1, 3,  // 第一个三角形
	//1, 2, 3   // 第二个三角形
	//};

	// 局部空间坐标
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

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 位置属性
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//// 颜色属性
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	//glEnableVertexAttribArray(1);

	// 纹理坐标
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	//glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// 加载并创建第一个纹理（opengl保证至少有16个纹理单元可供使用）
	unsigned int texture1;   // 如果要加载多个纹理，这里设置为数组
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 缩小操作时过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 放大操作时过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// 加载纹理图片并附到纹理对象上
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // 告诉stb_image.h在y轴上翻转加载的纹理,后面加载的所有纹理图片都将翻转
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// 当调用glTexImage2D时，当前绑定的纹理对象就会被附加上纹理图像
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);   // 生成多级渐远纹理
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// 生成了纹理和相应的多级渐远纹理后，释放图像的内存
	stbi_image_free(data);


	// 加载并创建第二个纹理
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// 为当前绑定的第二个纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// 加载纹理图片并附到纹理对象上
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// awesomeface.png具有透明度，因此是alpha通道，所以一定要告诉OpenGL数据类型是GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	// 解除绑定
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	// 告诉opengl每个采样器属于哪个纹理单元(只需要做一次)
	ourShader.use();  // 在设置uniform之前，不要忘记激活/使用着色器
	//glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture1"), 0);
	ourShader.setInt("ourTexture1", 0);
	ourShader.setInt("ourTexture2", 1);

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -5.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);  // 清理颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清理颜色缓冲和深度缓冲


		ourShader.setFloat("mixValue", mixValue);  // 循环前调用了use()，所以可以设置uniform

		glActiveTexture(GL_TEXTURE0);  // 在绑定纹理之前先激活纹理单元,只有一个纹理时,可以不用手动激活，默认激活
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glm::mat4 view = glm::mat4(1.0f);   // 初始化观察矩阵
		// 观察矩阵通常是由一系列的位移和旋转的组合来完成，平移/旋转场景从而使得特定的对象被变换到摄像机的前方
		view = glm::translate(view, glm::vec3(view_x, view_y, view_z));

		glm::mat4 projection = glm::mat4(1.0f);  // 初始化投影矩阵
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		//int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");

		// 设置uniform变量之前必须先激活着色器程序对象
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

		// 绑定VAO后会绑定纹理,它会自动把纹理赋值给片段着色器的采样器
		glBindVertexArray(VAO);   // 前面并没有把VAO解绑定，其实这里不重新绑定也是可以的，但有多个VAO就需要绑定
		//glDrawArrays(GL_TRIANGLES, 0, 3);   // 从顶点数组对象中进行绘制
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   // 矩形由两个三角形组成，故是6个顶点,画第一个箱子,会使用当前绑定的索引缓冲对象中的索引进行绘制
		// 循环改变10次模型矩阵，并绘10个箱子
		for (unsigned int i = 0; i < 10; ++i)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i+1);
			//if (i % 3 == 0)
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

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
	glViewport(0, 0, width, height);  // 视口
}


// 处理所有输入:查询GLFW是否按下/释放了此帧的相关键，并做出相应的反应
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // 键盘esc
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)     // 键盘up
	{
		//mixValue += 0.01f;
		//if (mixValue >= 1.0f)
		//	mixValue = 1.0f;
		view_z += 0.1f;
		std::cout << "view_z = " << view_z << std::endl;

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  // 键盘down
	{
		//mixValue -= 0.01f;
		//if (mixValue <= 0.0f)
		//	mixValue = 0.0f;
		view_z -= 0.1f;
		std::cout << "view_z = " << view_z << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		view_x -= 0.1f;
		std::cout << "view_x = " << view_x << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		view_x += 0.1f;
		std::cout << "view_x = " << view_x << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		view_y -= 0.1f;
		std::cout << "view_y = " << view_x << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		view_y += 0.1f;
		std::cout << "view_y = " << view_y << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}





