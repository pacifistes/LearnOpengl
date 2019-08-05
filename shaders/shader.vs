#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec2 texture_coord;
flat out vec3 face_color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	texture_coord = vec2(position.z, position.y);
	face_color = color;
}
