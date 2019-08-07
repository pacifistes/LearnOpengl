/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 04:52:13 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/07 08:18:35 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		clear_mesh(t_mesh *mesh)
{
	free(mesh->vertices);
	free(mesh->indices);
	free(mesh);
}

static void	count_datas(t_mesh *mesh, char *filename)
{
	t_reader	reader;
	float		vertice[4];
	int			indice[4];
	int			nbr_indice;

	reader.fd = open(filename, O_RDONLY);
	while ((reader.ret = get_next_line(reader.fd, &reader.line)) > 0)
	{
		if (reader.line[0] == 'v' && load_vertice(reader.line, vertice))
			mesh->nbr_vertices++;
		else if (reader.line[0] == 'f')
		{
			nbr_indice = load_face(reader.line, indice);
			if (nbr_indice >= 3)
				mesh->nbr_indices += (nbr_indice == 3) ? 1 : 2;
		}
		ft_strdel(&reader.line);
	}
	if (reader.ret != 0)
		return ;
	ft_strdel(&reader.line);
	close(reader.fd);
}

static void	register_datas(t_mesh *mesh, char *filename)
{
	t_reader	reader;
	t_indices	mesh_indices;
	float		vertice[3];
	int			indice[4];
	int			nbr_indice;

	reader.fd = open(filename, O_RDONLY);
	ft_bzero(&mesh_indices, sizeof(t_indices));
	while ((reader.ret = get_next_line(reader.fd, &reader.line)) > 0)
	{
		if (reader.line[0] == 'v' && load_vertice(reader.line, vertice))
			register_vertice(mesh, &mesh_indices, vertice);
		else if (reader.line[0] == 'f')
		{
			nbr_indice = load_face(reader.line, indice);
			if (nbr_indice >= 3)
				register_faces(mesh, &mesh_indices, indice, nbr_indice);
		}
		ft_strdel(&reader.line);
	}
	if (reader.ret != 0)
		return ;
	ft_strdel(&reader.line);
	close(reader.fd);
}

static void	align_mesh(t_mesh *mesh)
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

t_mesh		*load(char *filename)
{
	t_mesh	*mesh;

	srand(time(NULL));
	mesh = ft_memalloc(sizeof(t_mesh));
	if (!mesh)
		return (NULL);
	count_datas(mesh, filename);
	if (!mesh->nbr_indices || !mesh->nbr_vertices)
	{
		free(mesh);
		return (NULL);
	}
	mesh->nbr_vertices *= 4;
	mesh->nbr_indices *= 3;
	mesh->vertices = ft_memalloc(sizeof(float) * mesh->nbr_vertices);
	mesh->indices = ft_memalloc(sizeof(unsigned int) * mesh->nbr_indices);
	register_datas(mesh, filename);
	align_mesh(mesh);
	return (mesh);
}
