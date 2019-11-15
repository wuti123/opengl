#include "glad/glad.h"
#include <glfw3.h>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main()
{
	glfwInit();
	// 基于OpenGL 3.3版本展开讨论的，所以我们需要告诉GLFW我们要使用的OpenGL版本是3.3
	// 将主版本号(Major)和次版本号(Minor)都设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// 明确告诉GLFW我们使用的是核心模式(Core-profile)
	// 明确告诉GLFW我们需要使用核心模式意味着我们只能使用OpenGL功能的一个子集
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// glfwCreateWindow函数需要窗口的宽和高作为它的前两个参数。第三个参数表示这个窗口的名称（标题）
	// 这个函数将会返回一个GLFWwindow对象，我们会在其它的GLFW操作中使用到。
	// 创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// 此函数使调用线程上指定窗口的OpenGL或OpenGL ES上下文处于当前状态。一个上下文每次只能在一个线程上成为当前的，而且每个线程每次只能有一个当前上下文。
	// 在线程之间移动上下文时，必须使旧线程上的上下文为非当前上下文，然后才能使新线程上的上下文为当前上下文。默认情况下，使上下文非current隐式地强制管道刷新。
	// 创建完窗口后通知GLFW将我们窗口的上下文(context)设置为当前线程的主上下文了。
	glfwMakeContextCurrent(window);

	// GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD
	// 我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数
	// GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// 开始渲染之前. 必须告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	// 这样OpenGL才能知道怎样根据窗口大小显示数据和坐标。我们可以通过调用glViewport函数来设置窗口的维度(Dimension)
	// glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
	// 实际上也可以将视口的维度设置为比GLFW的维度小，这样子之后所有的OpenGL渲染将会在一个更小的窗口中显示，这样子的话我们也可以将一些其它元素显示在OpenGL视口之外。
	//glViewport(0, 0, 800, 600);

	// 注册回调函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 渲染循环(Render Loop)
	// glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
	// glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
	// glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 释放/删除之前分配的所有资源
	glfwTerminate();

	return 0;
}