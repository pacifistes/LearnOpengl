#version 410 core

// layout (location = 0) in vec3 aPos;

out vec4 FragColor;
// in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}