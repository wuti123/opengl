#include "../include/shader.h"


// 构造读取并构造着色器
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	// 从文件路径中获取顶点/片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	// 保证ifstream对象可以抛出异常：
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// 打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		
		std::stringstream vShaderStream, fShaderStream;  // try之外无法访问try里面定义的变量
		
		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();

		// 转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// string转换为char*
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	// 顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// 检测编译是否成功
	checkCompileErrors(vertex, "VERTEX");

	// 片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// 检测编译是否成功
	checkCompileErrors(fragment, "FRAGMENT");

	// 如果给定了几何着色器，编译几何着色器
	unsigned int geometry;
	if (geometryPath != nullptr)
	{
		const char* gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		// 检测编译是否成功
		checkCompileErrors(geometry, "GEOMETRY");
	}

	// 着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (geometryPath != nullptr)
	{
		glAttachShader(ID, geometry);
	}
	glLinkProgram(ID);
	// 检测着色器链接是否成功
	checkCompileErrors(ID, "PROGRAM");

	// 链接成程序之后就不需要着色器对象了
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr)
		glDeleteShader(geometry);
}


// 使用激活程序
void Shader::use()
{
	glUseProgram(ID);
}


// uniform工具函数
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	if (glGetUniformLocation(ID, name.c_str()) == -1)
	{
		std::cout << "Don't find " << name.c_str() << std::endl;
	}
}



// 用于检查着色器编译/链接错误的实用函数
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int  success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- ------------------------------------ -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------- -- " << std::endl;
		}
	}

}