/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ressources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:57:39 by bbrunell          #+#    #+#             */
/*   Updated: 2019/06/13 18:04:59 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	clear_ressources(t_gl_buffers *buffers)
{
	glDeleteVertexArrays(1, &buffers->vao);
	glDeleteBuffers(1, &buffers->vbo);
	glDeleteBuffers(1, &buffers->ebo);
	glfwTerminate();
}