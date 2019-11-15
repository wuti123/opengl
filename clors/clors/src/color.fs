#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;  // ������ɫ
uniform vec3 lightColor;   // ��Դ��ɫ

void main()
{
	FragColor = vec4(lightColor * objectColor, 1.0);
}