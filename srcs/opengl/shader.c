/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:20:46 by bbrunell          #+#    #+#             */
/*   Updated: 2019/06/25 16:02:16 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char	*read_file(char *filename)
{
	FILE *file;
	char *str;
	long fsize;

	file = fopen(filename, "rb");
	if (file == NULL)
		return (NULL);
	fseek(file, 0, SEEK_END);
	fsize = ftell(file);
	rewind(file);
	str = malloc(fsize + 1);
	fread(str, 1, fsize, file);
	fclose(file);
	str[fsize] = 0;
	return (str);
}

void	check_shaders(GLuint vertex_shader, GLuint fragment_shader,
GLuint shader_program)
{
	int success;
	int success2;
	int success3;

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success2);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success3);
	if (!success || !success2 || !success3)
		ft_printf("error in shader file\n");
}

GLuint	create_shader(char *path, GLenum shader_type)
{
	GLuint	shader;
	GLint	success;
	char	*str;

	str = read_file(path);
	if (!str)
	{
		ft_printf("Error in shader path: \"%s\"\n", path);
		return (0);
	}
	shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, (const char **)&str, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
		ft_printf("Error compile shader: \"%s\"\n", path);
	ft_strdel(&str);
	return (shader);
}

GLuint	init_shader(char *vs_filename, char *fs_filename)
{
	GLuint	vertex_shader;
	GLuint	fragment_shader;
	GLuint	shader_program;
	GLint	success;

	vertex_shader = create_shader(vs_filename, GL_VERTEX_SHADER);
	fragment_shader = create_shader(fs_filename, GL_FRAGMENT_SHADER);
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
		ft_printf("Error compile shader program\n");
	return (shader_program);
}
