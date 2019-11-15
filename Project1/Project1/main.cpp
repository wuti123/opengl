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
	// ����OpenGL 3.3�汾չ�����۵ģ�����������Ҫ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	// �����汾��(Major)�ʹΰ汾��(Minor)����Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	// ��ȷ����GLFW������Ҫʹ�ú���ģʽ��ζ������ֻ��ʹ��OpenGL���ܵ�һ���Ӽ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// glfwCreateWindow������Ҫ���ڵĿ�͸���Ϊ����ǰ����������������������ʾ������ڵ����ƣ����⣩
	// ����������᷵��һ��GLFWwindow�������ǻ���������GLFW������ʹ�õ���
	// �����괰�����ǾͿ���֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳����������ˡ�
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	// �˺���ʹ�����߳���ָ�����ڵ�OpenGL��OpenGL ES�����Ĵ��ڵ�ǰ״̬��һ��������ÿ��ֻ����һ���߳��ϳ�Ϊ��ǰ�ģ�����ÿ���߳�ÿ��ֻ����һ����ǰ�����ġ�
	// ���߳�֮���ƶ�������ʱ������ʹ���߳��ϵ�������Ϊ�ǵ�ǰ�����ģ�Ȼ�����ʹ���߳��ϵ�������Ϊ��ǰ�����ġ�Ĭ������£�ʹ�����ķ�current��ʽ��ǿ�ƹܵ�ˢ�¡�
	// �����괰�ں�֪ͨGLFW�����Ǵ��ڵ�������(context)����Ϊ��ǰ�̵߳����������ˡ�
	glfwMakeContextCurrent(window);

	// GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
	// ���Ǹ�GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
	// GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ�����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// ��ʼ��Ⱦ֮ǰ. �������OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)
	// ����OpenGL����֪���������ݴ��ڴ�С��ʾ���ݺ����ꡣ���ǿ���ͨ������glViewport���������ô��ڵ�ά��(Dimension)
	// glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
	// ʵ����Ҳ���Խ��ӿڵ�ά������Ϊ��GLFW��ά��С��������֮�����е�OpenGL��Ⱦ������һ����С�Ĵ�������ʾ�������ӵĻ�����Ҳ���Խ�һЩ����Ԫ����ʾ��OpenGL�ӿ�֮�⡣
	//glViewport(0, 0, 800, 600);

	// ע��ص�����������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��Ⱦѭ��(Render Loop)
	// glfwWindowShouldClose����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
	// glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
	// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �ͷ�/ɾ��֮ǰ�����������Դ
	glfwTerminate();

	return 0;
}