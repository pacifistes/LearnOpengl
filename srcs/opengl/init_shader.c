/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:20:46 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/15 14:50:20 by bbrunell         ###   ########.fr       */
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
	char	*s_vertex;
	char	*s_fragment;

	s_vertex = read_file("./shaders/shader.vs");
	s_fragment = read_file("./shaders/shader.fs");
	if (s_vertex == NULL || s_fragment == NULL)
		ft_exit("Error in shaders path.");
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const char **)&s_vertex, NULL);
	glCompileShader(vertex_shader);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const char **)&s_fragment, NULL);
	glCompileShader(fragment_shader);
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	ft_strdel(&s_fragment);
	ft_strdel(&s_vertex);
	return (shader_program);
}