#version 410 core



out vec4 fragment_color;
in vec2 texture_coord;
flat in vec3 face_color;

uniform float texture_ratio;
uniform sampler2D obj_texture;

void main()
{
	fragment_color = vec4(texture(obj_texture, texture_coord).rgb * texture_ratio
	+ face_color * (1.0 - texture_ratio), 1.0f);
}