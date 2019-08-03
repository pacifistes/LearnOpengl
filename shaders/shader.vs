#version 410 core

layout (location = 0) in vec4 aPos;
// layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 test;

void main()
{
	gl_Position = projection * view * model * aPos;
	// gl_Position = vec4(aPos, 1.0f);
	TexCoord = vec2(aPos.x, aPos.y);
}
