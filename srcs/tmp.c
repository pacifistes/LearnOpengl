/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:07:26 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/04 01:33:03 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	print_mesh(t_mesh *mesh)
{
	unsigned int i;

	i = 0;
	while (i < mesh->nbr_vertices)
	{
		printf("v %f %f %f %f\n", mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2], mesh->vertices[i + 3]);
		i += 4;
	}
	i = 0;
	while (i < mesh->nbr_indices)
	{
		printf("f %u %u %u\n", mesh->indices[i], mesh->indices[i + 1], mesh->indices[i + 2]);
		i += 3;
	}
}

t_mesh	*cube_mesh(void)
{
	static float		vertices[] = {
	1.000000, 0.500000, 0.500000, 1.000000,
	1.000000, 0.500000, 1.000000, 1.000000,
	0.500000, 0.500000, 1.000000, 1.000000,
	0.500000, 0.500000, 0.500000, 1.000000,
	1.000000, 1.000000, 0.5, 1.000000,
	0.999999, 1.000000, 1.000001, 1.000000,
	0.500000, 1.000000, 1.000000, 1.000000,
	0.500000, 1.000000, 0.500000, 1.000000
	};
	static unsigned int	indices[] = {
		1, 3, 0, 7, 5, 4, 4, 1, 0, 5, 2, 1,
		2, 7, 3, 0, 7, 4, 1, 2, 3, 7, 6, 5,
		4, 5, 1, 5, 6, 2, 2, 6, 7, 0, 3, 7,
	};
	t_mesh				*mesh;

	mesh = ft_memalloc(sizeof(t_mesh));
	mesh->vertices = (float *)malloc(sizeof(float) * 32);
	ft_memcpy(mesh->vertices, vertices, sizeof(float) * 32);
	mesh->indices = (unsigned int *)malloc(sizeof(unsigned int) * 36);
	ft_memcpy(mesh->indices, indices, sizeof(unsigned int) * 36);
	mesh->nbr_indices = 36;
	mesh->nbr_vertices = 32;
	return (mesh);
}
