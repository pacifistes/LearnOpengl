#version 410 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
// out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 test;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	// gl_Position = projection * view * vec4(aPos, 1.0f);
	// gl_Position = test * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
	// Color = aColor;
}


// mat4 rotationMatrix(vec3 axis, float angle)
// {
// 	axis = normalize(axis);
// 	float s = sin(angle);
// 	float c = cos(angle);
// 	float oc = 1.0 - c;
	
// 	return mat4(oc * axis.x * axis.x + c,          oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
// 				oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c,          oc * axis.y * axis.z - axis.x * s, 0.0,
// 				oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c,          0.0,
// 				0.0,                               0.0,                               0.0,                               1.0);
// }

// void main()
// {
// 	mat4 pm = mat4(	1, 0, 0, 0, 
// 					0, 1, 0, 0,
// 					0, 0, 0, 0,
// 					0, 0, 1, 0);
// 	gl_Position = rotationMatrix(vec3(0, 1, 0), 0) * (vec4(aPos, 1.0)) * pm;
// 	TexCoord = aTexCoord;
// 	Color = aColor;
// }