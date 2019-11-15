#version 330 core

out vec4 FragColor;

struct Material
{
//	vec3  ambient;    // 定义了在环境光照下物体反射的颜色，通常于物体颜色相同
//	vec3  diffuse;    // 定义在漫反射光照下物体的颜色（和环境光照一样）

	sampler2D diffuse; // 定义采样器

	vec3  specular;   // 设置的是镜面光照对物体的颜色影响
	float shininess;  // 镜面高光的散射(如：32)
};

struct Light
{
	vec3 position;    // 光源位置

	// 三种光照的不同强度
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;         // 纹理坐标
in vec3 Normal;            // 法线向量（世界坐标系下）
in vec3 FragPos;           // 片段位置（世界坐标系下）

uniform vec3 viewPos;      // 观察者（摄像机对象）的位置坐标
//uniform vec3 objectColor;  // 物体颜色
//uniform vec3 lightColor;   // 光源颜色
uniform Material material;
uniform Light light;


void main()
{
	// ambient
	//vec3 ambient = light.ambient * material.ambient;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse(漫反射)
	vec3 norm     = normalize(Normal);                                                  // 标准化法线向量
	vec3 lightDir = normalize(light.position - FragPos);                                // 标准化光照方向向量,世界坐标系下的片段位置坐标指向光源点（OA-OB = BA）
	float diff    = max(dot(norm, lightDir), 0.0);                                      // 计算法线与光照方向向量夹角余弦值，夹角大于90°返回的是负值，顾需要加max()函数来约束
	vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  // 计算每一个片段光照漫反射分量的颜色值,从纹理中采样片段的漫反射颜色值

	// specular(镜面反射)                                  
	vec3 viewDir    = normalize(viewPos - FragPos);                                     // 片段到观察者的方向向量
	vec3 reflectDir = reflect(-lightDir, norm);                                         // 沿着法线轴的反射向量，reflect()函数要求第一个参数是从光源指向片段位置的向量
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);      // 计算反射向量与观察者向量的夹角余弦值的32倍
	vec3 specular   = light.specular * (spec * material.specular);                      // 镜面分量
	

	//vec3 result = (ambient + diffuse + specular) * objectColor;  // 计算光照环境分量与漫反射分量作用下物体的最终颜色值
	vec3 result = ambient + diffuse + specular;
	FragColor   = vec4(result, 1.0f);
}