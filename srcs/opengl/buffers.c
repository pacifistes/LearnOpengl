/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 17:54:51 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/06 17:13:01 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_buffers(t_gl_buffers *buffers, t_mesh *mesh)
{
	//  float vertices[] = {
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };
    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 3,  // first Triangle
    //     1, 2, 3   // second Triangle
    // };
	(void)buffers;
	(void)mesh;
	glGenVertexArrays(1, &buffers->vao);
	glGenBuffers(1, &buffers->vbo);
	glGenBuffers(1, &buffers->ebo);
	glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), mesh->vertices,
	GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->indices), mesh->indices,
	GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(6 * sizeof(float)));
	// glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// for each face
//   for each vertex in face
//       key = fn(position_index,normal_index,texcoord_index)
//       if vertices.find(key)
//         new_index = vertex(key).index
//       else
//         create vertex from position/normal/texcorrd
//         store new vertex in vertices with key and next_vertex
//         new_index = next_vertex
//         increment next_index
//       end
//       save new_index in index buffer
//   loop
