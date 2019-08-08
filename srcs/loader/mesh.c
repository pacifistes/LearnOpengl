/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 07:44:38 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/08 12:46:04 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		align_mesh(t_mesh *mesh)
{
	t_vector	min;
	t_vector	max;
	int			i;

	i = 0;
	min = new_vector(mesh->vertices[0], mesh->vertices[1], mesh->vertices[2]);
	max = new_vector(min.x, min.y, min.z);
	while (i < (int)mesh->nbr_vertices)
	{
		min.x = fminf(min.x, mesh->vertices[i]);
		min.y = fminf(min.y, mesh->vertices[i + 1]);
		min.z = fminf(min.z, mesh->vertices[i + 2]);
		max.x = fmaxf(max.x, mesh->vertices[i]);
		max.y = fmaxf(max.y, mesh->vertices[i + 1]);
		max.z = fmaxf(max.z, mesh->vertices[i + 2]);
		i += 4;
	}
	i = 0;
	while (i < (int)mesh->nbr_vertices)
	{
		mesh->vertices[i] = mesh->vertices[i] - (min.x + max.x) / 2;
		mesh->vertices[i + 1] = mesh->vertices[i + 1] - (min.y + max.y) / 2;
		mesh->vertices[i + 2] = mesh->vertices[i + 2] - (min.z + max.z) / 2;
		i += 4;
	}
}

t_vertice	*get_vertice(t_vertice *vertices, int index)
{
	int	i;

	i = 0;
	while (vertices)
	{
		if (i == index)
			return (vertices);
		i++;
		vertices = vertices->next;
	}
	return (NULL);
}

void		transfer_to_mesh(t_mesh *mesh, t_datas *datas)
{
	t_transfer_env	t;

	ft_bzero(&t, sizeof(t_transfer_env));
	t.faces = datas->faces;
	while (t.faces)
	{
		if (is_valid_face(t.faces, mesh->nbr_vertices / 4))
		{
			t.color = 0.3 + (double)(rand() / (double)(RAND_MAX)) * (1.0 - 0.3);
			t.j = -1;
			while (++t.j < 3)
			{
				t.vertice = get_vertice(datas->vertices,
				t.faces->indices[t.j].vertice - 1);
				mesh->vertices[t.index] = t.vertice->x;
				mesh->vertices[t.index + 1] = t.vertice->y;
				mesh->vertices[t.index + 2] = t.vertice->z;
				mesh->vertices[t.index + 3] = t.color;
				mesh->indices[t.i + t.j] = t.i + t.j;
				t.index += 4;
			}
			t.i += 3;
		}
		t.faces = t.faces->next;
	}
}

t_mesh		*convert_to_mesh(t_datas *datas)
{
	t_mesh	*mesh;
	int		nbr_vertices;
	int		nbr_faces;

	nbr_vertices = count_vertices(datas->vertices);
	nbr_faces = count_faces(datas->faces, nbr_vertices);
	mesh = ft_memalloc(sizeof(t_mesh));
	if (!mesh)
		return (NULL);
	mesh->nbr_vertices = nbr_faces * 4 * 3;
	mesh->nbr_indices = nbr_faces * 3;
	mesh->vertices = ft_memalloc(sizeof(float) * mesh->nbr_vertices);
	mesh->indices = ft_memalloc(sizeof(unsigned int) * mesh->nbr_indices);
	transfer_to_mesh(mesh, datas);
	return (mesh);
}

void		clear_mesh(t_mesh *mesh)
{
	free(mesh->vertices);
	free(mesh->indices);
	free(mesh);
}
