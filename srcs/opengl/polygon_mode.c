/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:01:33 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/17 17:57:49 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	change_polygon_mode()
{
	static const GLenum modes[] = {
		GL_POINT,
		GL_LINE,
		GL_FILL,
	};
	GLint actual_mode;
	int i;

	glGetIntegerv(GL_POLYGON_MODE, &actual_mode);
	i = 0;
	while (i < 3)
	{
		if (modes[i] == (GLenum) actual_mode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, modes[(i + 1) % 3]);
			return;
		}
		i++;
	}
}