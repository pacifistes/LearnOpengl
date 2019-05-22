#version 410 core

layout (location = 0) in vec3 aPos;
out vec4 FragColor;

in vec2 TexCoord;
// in vec3 Color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(Color, 1.0);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	// FragColor = vec4(1,0, 0,  1.0f);
}