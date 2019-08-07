/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 03:30:17 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/07 07:48:53 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	register_vertice(t_mesh *mesh, t_indices *mesh_indices,
float vertice[3])
{
	mesh->vertices[mesh_indices->i_vertices] = vertice[0];
	mesh->vertices[mesh_indices->i_vertices + 1] = vertice[1];
	mesh->vertices[mesh_indices->i_vertices + 2] = vertice[2];
	mesh_indices->i_vertices += 4;
}

void	register_face(t_mesh *mesh, t_indices *mesh_indices,
int indice[3])
{
	float	color;
	int		i;

	i = 0;
	color = 0.3 + (double)(rand() / (double)(RAND_MAX)) * (1.0 - 0.3);
	while (i < 3)
	{
		mesh->indices[mesh_indices->i_indices] = indice[i] - 1;
		if (indice[i] - 1 >= 0 && indice[i] - 1 < (int)mesh->nbr_vertices)
			mesh->vertices[(indice[i] - 1) * 4 + 3] = color;
		i++;
		mesh_indices->i_indices++;
	}
}

void	register_faces(t_mesh *mesh, t_indices *mesh_indices,
int indice[4], int nbr_indice)
{
	int tab[3];

	if (nbr_indice == 3)
	{
		tab[0] = indice[0];
		tab[1] = indice[1];
		tab[2] = indice[2];
		register_face(mesh, mesh_indices, tab);
	}
	else if (nbr_indice == 4)
	{
		tab[0] = indice[0];
		tab[1] = indice[1];
		tab[2] = indice[3];
		register_face(mesh, mesh_indices, tab);
		tab[0] = indice[1];
		tab[1] = indice[2];
		tab[2] = indice[3];
		register_face(mesh, mesh_indices, tab);
	}
}

int		load_vertice(char *str, float vertice[3])
{
	return (sscanf(str, "v %f %f %f",
	&vertice[0], &vertice[1], &vertice[2]));
}

int		load_face(char *str, int indice[4])
{
	return (sscanf(str, "f %d %d %d %d",
			&indice[0], &indice[1], &indice[2], &indice[3]));
}
