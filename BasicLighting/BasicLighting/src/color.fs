#version 330 core

in vec3 Normal;            // 法线向量（世界坐标系下）
in vec3 FragPos;           // 片段位置（世界坐标系下）

out vec4 FragColor;

uniform vec3 lightPos;     // 光源位置
uniform vec3 viewPos;      // 观察者（摄像机对象）的位置坐标
uniform vec3 objectColor;  // 物体颜色
uniform vec3 lightColor;   // 光源颜色

void main()
{
	// ambient
	float ambientStrength = 0.1;                   // 环境光照，确保场景中没有直接的光源也能有一些发散的光
	vec3 ambient = ambientStrength * lightColor;   // 环境分量颜色值

	// diffuse(漫反射)
	vec3 norm     = normalize(Normal);             // 标准化法线向量
	vec3 lightDir = normalize(lightPos - FragPos); // 标准化光照方向向量,世界坐标系下的片段位置坐标指向光源点（OA-OB = BA）
	float diff    = max(dot(norm, lightDir), 0.0); // 计算法线与光照方向向量夹角余弦值，夹角大于90°返回的是负值，顾需要加max()函数来约束
	vec3 diffuse  = diff * lightColor;             // 计算每一个片段光照漫反射分量的颜色值

	// specular(镜面反射)
	float specularStrength = 1;                                   // 镜面强度
	vec3 viewDir    = normalize(viewPos - FragPos);                 // 片段到观察者的方向向量
	vec3 reflectDir = reflect(-lightDir, norm);                     // 沿着法线轴的反射向量，reflect()函数要求第一个参数是从光源指向片段位置的向量
	float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 256);  // 计算反射向量与观察者向量的夹角余弦值的32倍
	vec3 specular   = specularStrength * spec * lightColor;         // 镜面分量
	

	vec3 result = (ambient + diffuse + specular) * objectColor;  // 计算光照环境分量与漫反射分量作用下物体的最终颜色值
	FragColor   = vec4(result, 1.0f);
}