/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:20:46 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/13 17:55:12 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// Shaders
// const GLchar* vertex_shaderSource = "#version 410 core\n"
//     "layout (location = 0) in vec3 position;\n"
//     "void main()\n"
//     "{\n"
//     "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//     "}\0";
// // const GLchar* fragment_shaderSource = "#version 410 core\n"
// //     "out vec4 color;\n"
// //     "void main()\n"
// //     "{\n"
// //     "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
// //     "}\n\0";


// const GLchar* fragment_shaderSource =
// 	"#version 410 core\n"
//     "out vec4 color;\n"
//     "uniform vec4 ourColor;\n"
// 	"void main()\n"
//     "{\n"
//     "color = ourColor;\n"
//     "}\n\0";

// const GLchar* vertex_shaderSource = "#version 410 core\n"
//     "layout (location = 0) in vec3 position;\n"
//     "layout (location = 1) in vec3 color;\n"
//     "out vec3 ourColor;\n"
//     "void main()\n"
//     "{\n"
//     "gl_Position = vec4(position, 1.0);\n"
//     "ourColor = color;\n"
//     "}\0";

const GLchar* vertex_shaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
	"layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
	"out vec2 TexCoord;\n"
	"uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
	"gl_Position = transform * vec4(position, 1.0f);\n"
    "ourColor = color;\n"
	"TexCoord = aTexCoord;\n"
    "}\0";


const GLchar* fragment_shaderSource = "#version 410 core\n"
    "in vec3 ourColor;\n"
	"in vec2 TexCoord;\n"
    "out vec4 color;\n"
	"uniform sampler2D ourTexture;\n"
    "void main()\n"
    "{\n"
    "color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
    "}\n\0";

/*
**	Pour verifier si cela compile bien
**	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
**	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
**	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
*/
GLuint	init_shader(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint shader_program;

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shaderSource, NULL);
	glCompileShader(vertex_shader);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shaderSource, NULL);
	glCompileShader(fragment_shader);
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return (shader_program);
}