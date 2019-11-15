#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 Normal;              // ��������
out vec3 FragPos;             // Ƭ��λ��
out vec2 TexCoords;           // ��������

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// ע��˷�Ҫ��������������ȳ�ģ�;����ٹ۲����������͸��ͶӰ����
	FragPos = vec3(model * vec4(aPos, 1.0f));               // Ƭ��ת������������ϵ��
	Normal  = mat3(transpose(inverse(model))) * aNormal;    // �ѷ�������ת������������ϵ�£�������ֻ��һ������������ֻϣ������ʵʩ���ź���ת�任��ֻѡ��ģ�;�������Ͻ�3x3�����ұ���ʹ�õȱ�����

	gl_Position = projection * view * vec4(FragPos, 1.0f);
	TexCoords   = aTexCoords;
}