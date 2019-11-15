#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixValue;

void main()
{
	//FragColor = vec4(ourColor, 1.0f);
	//FragColor = texture(ourTexture, TexCoord);
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue);
	//FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}