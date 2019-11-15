//#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <vector>


// ��������ƶ��ļ�������ѡ�����������Զ�봰��ϵͳ�ض������뷽��
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
	// �������
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;      
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// ŷ����
	float Yaw;    // ƫ����
	float Pitch;  // ������

	// ���ѡ������
	float MovementSpeed;        // �ٶ�
	float MouseSensitivity;     // ������������
	float Zoom;                 // �������Ұ�Ƕ�

	// ����ֵ���캯��
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAM, float pitch = PITCH);

	// ����ֵ���캯��
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// ����ʹ��ŷ���Ǻ�LookAt�������Ĺ۲����
	glm::mat4 GetViewMatrix();

	// ������κ����Ƽ��̵�����ϵͳ���յ����롣�������������ENUM��ʽ���������(�Ӵ���ϵͳ�г���)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// ������������ϵͳ���յ������롣������x��y�����ϵ�ƫ������
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// ������������¼����յ����롣ֻ��Ҫ���봹ֱ����
	void ProcessMouseScroll(float yoffset);


private:
	// �������(���º��)ŷ���Ǽ���ǰʸ��
	void updateCameraVectors();
};




#endif