#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 Normal;              // 法线向量
out vec3 FragPos;             // 片段位置
out vec2 TexCoords;           // 纹理坐标

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// 注意乘法要从右往左读，即先乘模型矩阵，再观察矩阵，最后乘以透视投影矩阵
	FragPos = vec3(model * vec4(aPos, 1.0f));               // 片段转换到世界坐标系下
	Normal  = mat3(transpose(inverse(model))) * aNormal;    // 把法线向量转换到世界坐标系下，法向量只是一个方向响亮，只希望对他实施缩放和旋转变换，只选用模型矩阵的左上角3x3矩阵，且必须使用等比缩放

	gl_Position = projection * view * vec4(FragPos, 1.0f);
	TexCoords   = aTexCoords;
}