//#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>   // OpenGL Mathematics

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	// 着色器程序ID
	unsigned int ID;

	// 构造着色器
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	// 使用激活程序
	void use();

	// uniform工具函数,要设置uniform，必须要激活函数之后，即调用use()之后
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;

	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;

	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;

	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	
	void setMat3(const std::string &name, const glm::mat3 &mat) const;

	void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	// 用于检查着色器编译/链接错误的实用函数
	void checkCompileErrors(unsigned int shader, std::string type);

};

#endif