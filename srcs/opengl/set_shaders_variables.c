/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shaders_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:37:18 by bbrunell          #+#    #+#             */
/*   Updated: 2019/06/13 20:38:24 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_matrice(GLuint shader, char *str, GLfloat *matrice)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrice);
}

void	set_vector(GLuint shader, char *str, t_vector vector)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void	set_int(GLuint shader, char *str, GLint value)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniform1i(location, value);
}

void	set_float(GLuint shader, char *str, GLfloat value)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniform1f(location, value);
}