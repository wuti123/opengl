#version 330 core

out vec4 FragColor;

struct Material
{
//	vec3  ambient;    // �������ڻ������������巴�����ɫ��ͨ����������ɫ��ͬ
//	vec3  diffuse;    // ������������������������ɫ���ͻ�������һ����

	sampler2D diffuse; // ���������

	vec3  specular;   // ���õ��Ǿ�����ն��������ɫӰ��
	float shininess;  // ����߹��ɢ��(�磺32)
};

struct Light
{
	vec3 position;    // ��Դλ��

	// ���ֹ��յĲ�ͬǿ��
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;         // ��������
in vec3 Normal;            // ������������������ϵ�£�
in vec3 FragPos;           // Ƭ��λ�ã���������ϵ�£�

uniform vec3 viewPos;      // �۲��ߣ���������󣩵�λ������
//uniform vec3 objectColor;  // ������ɫ
//uniform vec3 lightColor;   // ��Դ��ɫ
uniform Material material;
uniform Light light;


void main()
{
	// ambient
	//vec3 ambient = light.ambient * material.ambient;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse(������)
	vec3 norm     = normalize(Normal);                                                  // ��׼����������
	vec3 lightDir = normalize(light.position - FragPos);                                // ��׼�����շ�������,��������ϵ�µ�Ƭ��λ������ָ���Դ�㣨OA-OB = BA��
	float diff    = max(dot(norm, lightDir), 0.0);                                      // ���㷨������շ��������н�����ֵ���нǴ���90�㷵�ص��Ǹ�ֵ������Ҫ��max()������Լ��
	vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  // ����ÿһ��Ƭ�ι����������������ɫֵ,�������в���Ƭ�ε���������ɫֵ

	// specular(���淴��)                                  
	vec3 viewDir    = normalize(viewPos - FragPos);                                     // Ƭ�ε��۲��ߵķ�������
	vec3 reflectDir = reflect(-lightDir, norm);                                         // ���ŷ�����ķ���������reflect()����Ҫ���һ�������Ǵӹ�Դָ��Ƭ��λ�õ�����
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);      // ���㷴��������۲��������ļн�����ֵ��32��
	vec3 specular   = light.specular * (spec * material.specular);                      // �������
	

	//vec3 result = (ambient + diffuse + specular) * objectColor;  // ������ջ�����������������������������������ɫֵ
	vec3 result = ambient + diffuse + specular;
	FragColor   = vec4(result, 1.0f);
}