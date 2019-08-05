/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 17:54:51 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/05 05:02:47 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_buffers(t_gl_buffers *buffers, t_mesh *mesh)
{
	glGenVertexArrays(1, &buffers->vao);
	glGenBuffers(1, &buffers->vbo);
	glGenBuffers(1, &buffers->ebo);
	glBindVertexArray(buffers->vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->nbr_vertices,
	mesh->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	sizeof(unsigned int) * mesh->nbr_indices, mesh->indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
	(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
	(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
