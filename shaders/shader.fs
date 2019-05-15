#version 410 core

out vec4 color;
in vec3 ourColor;
in vec2 TexCoord;

// uniform sampler2D ourTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// color = vec4(ourColor, 1.0f);
	// color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
	// color = texture(texture2, TexCoord) * vec4(ourColor, 1.0);
	color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
}