//#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <vector>


// 定义相机移动的几个可能选项。用作抽象，以远离窗口系统特定的输入方法
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAM         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera
{
public:
	// 相机属性
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;      
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// 欧拉角
	float Yaw;    // 偏航角
	float Pitch;  // 俯仰角

	// 相机选项设置
	float MovementSpeed;        // 速度
	float MouseSensitivity;     // 鼠标滚轮灵敏度
	float Zoom;                 // 摄像机视野角度

	// 向量值构造函数
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAM, float pitch = PITCH);

	// 标量值构造函数
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// 返回使用欧拉角和LookAt矩阵计算的观察矩阵
	glm::mat4 GetViewMatrix();

	// 处理从任何类似键盘的输入系统接收的输入。接受摄像机定义ENUM形式的输入参数(从窗口系统中抽象)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// 处理从鼠标输入系统接收到的输入。期望在x和y方向上的偏移量。
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// 处理从鼠标滚轮事件接收的输入。只需要输入垂直轮轴
	void ProcessMouseScroll(float yoffset);


private:
	// 根据相机(更新后的)欧拉角计算前矢量
	void updateCameraVectors();
};




#endif