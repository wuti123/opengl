#version 330 core

in vec3 Normal;            // ������������������ϵ�£�
in vec3 FragPos;           // Ƭ��λ�ã���������ϵ�£�

out vec4 FragColor;

uniform vec3 lightPos;     // ��Դλ��
uniform vec3 viewPos;      // �۲��ߣ���������󣩵�λ������
uniform vec3 objectColor;  // ������ɫ
uniform vec3 lightColor;   // ��Դ��ɫ

void main()
{
	// ambient
	float ambientStrength = 0.1;                   // �������գ�ȷ��������û��ֱ�ӵĹ�ԴҲ����һЩ��ɢ�Ĺ�
	vec3 ambient = ambientStrength * lightColor;   // ����������ɫֵ

	// diffuse(������)
	vec3 norm     = normalize(Normal);             // ��׼����������
	vec3 lightDir = normalize(lightPos - FragPos); // ��׼�����շ�������,��������ϵ�µ�Ƭ��λ������ָ���Դ�㣨OA-OB = BA��
	float diff    = max(dot(norm, lightDir), 0.0); // ���㷨������շ��������н�����ֵ���нǴ���90�㷵�ص��Ǹ�ֵ������Ҫ��max()������Լ��
	vec3 diffuse  = diff * lightColor;             // ����ÿһ��Ƭ�ι����������������ɫֵ

	// specular(���淴��)
	float specularStrength = 1;                                   // ����ǿ��
	vec3 viewDir    = normalize(viewPos - FragPos);                 // Ƭ�ε��۲��ߵķ�������
	vec3 reflectDir = reflect(-lightDir, norm);                     // ���ŷ�����ķ���������reflect()����Ҫ���һ�������Ǵӹ�Դָ��Ƭ��λ�õ�����
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 256);  // ���㷴��������۲��������ļн�����ֵ��32��
	vec3 specular   = specularStrength * spec * lightColor;         // �������
	

	vec3 result = (ambient + diffuse + specular) * objectColor;  // ������ջ�����������������������������������ɫֵ
	FragColor   = vec4(result, 1.0f);
}