/*
	要记住把glad.c文件添加到工程里
*/


#include "glad/glad.h"
#include <glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
	glViewport(0, 0, width, height);
}


// 顶点着色器源码字符串
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// 片段着色器源码字符串
const char* fragmentShaderSOURCE = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


int main()
{
	// 用GLFW初始化窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();  // // 释放/删除之前分配的所有资源
		return -1;
	}

	// 此函数使调用线程上指定窗口的OpenGL或OpenGL ES上下文处于当前状态
	glfwMakeContextCurrent(window);

	// 初始化GLAD
	// 必须初始化GLAD，不然无法调用函数创建着色器对象或VBO对象
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// 告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 创建顶点着色器并编译
	unsigned int vertexShader = 0;  // 用ID来引用
	vertexShader = glCreateShader(GL_VERTEX_SHADER);    // 创建一个顶点着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);  // 把顶点着色器源码附加到顶点着色器对象上
	glCompileShader(vertexShader);                      // 编译顶点着色器
	
	// 检测顶点着色器是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// 创建片段着色器并编译
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSOURCE, NULL);  // 把片段着色器源码附加到片段着色器对象上
	glCompileShader(fragmentShader);

	// 检测片段着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// 创建着色器程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// 把着色器附加到程序上，然后用glLinkProgram链接
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// 检测链接着色器程序是否失败，并获取相应的日志。
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << endl;
	}

	// 把着色器对象链接到程序对象之后，删除着色器对象，我们不在需要它们了
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 创建顶点缓冲对象VBO，顶点数组对象VAO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);       // 使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
	// 复制顶点数组到缓冲中供OpenGL使用
	glBindVertexArray(VAO);  // 绑定VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定VBO，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER, 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	// 输入的顶点3D坐标
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, -0.7f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 把用户定义的数据复制到当前绑定缓冲

	// 告诉OpenGL该如何解析顶点数据,把顶点数据链接到顶点着色器的顶点属性上，即链接顶点属性
	// 每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);      // 启用顶点属性

	// 解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);  // 解除VBO的绑定
	glBindVertexArray(0);              // 解除VAO的绑定


	// 矩形
	float vertices1[] = {
	0.5f, 0.5f, 0.0f,     // 右上角
	0.5f, -0.5f, 0.0f,    // 右下角
	-0.5f, -0.5f, 0.0f,   // 左下角
	-0.5f, 0.5f, 0.0f     // 左上角
	};
	unsigned int indices[] = {  // 索引从0开始
		0, 1, 3,              // 第一个三角形
		1, 2, 3               // 第二个三角形
	};
	unsigned int VBO1, VAO1, EBO;
	glGenVertexArrays(1, &VAO1);   // 创建顶点数组对象
	glGenBuffers(1, &VBO1);        // 创建顶点缓冲对象
	glGenBuffers(1, &EBO);        // 创建索引缓冲对象

	glBindVertexArray(VAO1);       // 首先，绑定顶点数组对象

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);   // 绑定顶点数组对象之后再绑定顶点缓冲对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);   // 把6个顶点数据复制到缓冲

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);   // 在绑定VAO之后绑定VBO, 绑定VBO之后再绑定EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);   // 把索引复制到缓冲

	// 链接顶点属性
	// 每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);            // 启用顶点属性；顶点属性默认是禁用的

	// 注意，这是允许的，调用glVertexAttribPointer将VBO注册为顶点属性的绑定顶点缓冲区对象，
	// 这样我们就可以安全地解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 记住:当VAO处于活动状态时，不要解绑定EBO，因为绑定的元素缓冲区对象存储在VAO中;无论如何，保持EBO处于绑定状态。
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 您可以在之后解绑定VAO，这样其他的VAO调用就不会意外地修改这个VAO，但是这种情况很少发生。
	// 无论如何，修改其他VAOs都需要调用glBindVertexArray，所以当不直接需要时，我们通常不会解绑定VAOs(或VBOs)。
	glBindVertexArray(0);

	// 设置以线框模式绘制图像(即不填充模式)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		//// 激活着色器程序对象
		//glUseProgram(shaderProgram);
		//// 绘制前绑定配置好的VAO
		//glBindVertexArray(VAO);
		//// 绘制三角形
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// 激活着色器程序对象
		glUseProgram(shaderProgram);
		// 绘制前绑定配置好的VAO
		glBindVertexArray(VAO1);
		// 绘制矩形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);  // 交换颜色缓冲
		glfwPollEvents();         // 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
	}

	glfwTerminate();
	
	return 0;
}
