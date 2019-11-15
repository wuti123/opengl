#include "../include/camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
	Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

// �������(���º��)ŷ���Ǽ���ǰʸ��
void Camera::updateCameraVectors()
{
	// ���ݸ�����pitch��ƫ����yaw�������µ�ǰ����
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);  // ��һ��

	// ���¼�����������������
	// ���������й�һ������Ϊ���ǵĳ����������ϻ����¿��Ĵ��������Ӷ��ӽ���0����ᵼ���˶�����
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up    = glm::normalize(glm::cross(Right, Front));
}


// ������κ����Ƽ��̵�����ϵͳ���յ����롣�������������ENUM��ʽ���������(�Ӵ���ϵͳ�г���)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}


// ������������ϵͳ���յ������롣������x��y�����ϵ�ƫ������
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw   += xoffset;
	Pitch += yoffset;

	// ȷ������������pitch��������ʱ����Ļ���ᷭת
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 90.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}


// ������������¼����յ����롣ֻ��Ҫ���봹ֱ����
void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

// ����ʹ��ŷ���Ǻ�LookAt����������ͼ����
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}