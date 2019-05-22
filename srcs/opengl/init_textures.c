/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 09:25:09 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/22 15:16:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_textures(t_opengl *opengl)
{
	int				width;
	int				height;
	unsigned char	*image;
	unsigned char	*image2;

	glGenTextures(1, &opengl->texture);
	glBindTexture(GL_TEXTURE_2D, opengl->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = read_bmp("./assets/garfield.bmp", &width, &height);
	ft_printf("%d | %d", width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
	GL_BGR, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);


	glGenTextures(1, &opengl->texture2);
	glBindTexture(GL_TEXTURE_2D, opengl->texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image2 = read_bmp("./assets/odi.bmp", &width, &height);
	ft_printf("%d | %d\n", width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
	GL_BGR, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}