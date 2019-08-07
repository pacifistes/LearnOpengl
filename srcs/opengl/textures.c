/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 09:25:09 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/07 07:41:34 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** image = read_bmp("./assets/container_diffuse.bmp", &width, &height);
*/

GLuint	load_texture(char *filename)
{
	GLuint			texture;
	int				width;
	int				height;
	unsigned char	*image;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = read_bmp(filename, &width, &height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
	GL_BGR, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	free(image);
	return (texture);
}

void	active_textures(t_gl_textures *textures)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures->texture);
}

void	init_textures(t_gl_textures *textures, t_gl_shaders *shaders)
{
	textures->texture = load_texture("./assets/garfield.bmp");
	glUseProgram(shaders->shader);
	glUniform1i(glGetUniformLocation(shaders->shader, "obj_texture"), 0);
}
