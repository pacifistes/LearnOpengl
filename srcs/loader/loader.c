/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:21:55 by bbrunell          #+#    #+#             */
/*   Updated: 2019/06/08 15:54:54 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

unsigned int count_indices(t_face *faces)
{
	unsigned int	nbr_indices;

	nbr_indices = 0;
	while (faces)
	{
		nbr_indices++;
		faces = faces->next;
	}
	return(nbr_indices * 3);
}

unsigned int count_vertices(t_vertice *vertices)
{
	unsigned int nbr_vertices;

	nbr_vertices = 0;
	while (vertices)
	{
		nbr_vertices++;
		vertices = vertices->next;
	}
	return(nbr_vertices * 4);
}

static t_mesh	*convert_to_mesh(t_datas *datas)
{
	t_mesh	*mesh;
	int		i;

	if (datas == NULL)
		return (NULL);
	mesh = ft_memalloc(sizeof(t_mesh));
	mesh->nbr_vertices = count_vertices(datas->vertices);
	mesh->nbr_indices = count_indices(datas->faces);
	mesh->vertices = (float *)malloc(sizeof(float) * mesh->nbr_vertices);
	mesh->indices = (unsigned int *)malloc(sizeof(unsigned int) * mesh->nbr_indices);
	i = mesh->nbr_vertices - 1;
	while (datas->vertices && i >= 3)
	{
		mesh->vertices[i] = datas->vertices->w;
		mesh->vertices[i - 1] = datas->vertices->z;
		mesh->vertices[i - 2] = datas->vertices->y;
		mesh->vertices[i - 3] = datas->vertices->x;
		datas->vertices = datas->vertices->next;
		i -= 4;
	}
	i = mesh->nbr_indices - 1;
	while (datas->faces && i >= 2)
	{
		mesh->indices[i] = datas->faces->indices[0].vertice - 1;
		mesh->indices[i - 1] = datas->faces->indices[1].vertice - 1;
		mesh->indices[i - 2] = datas->faces->indices[2].vertice - 1;
		datas->faces = datas->faces->next;
		i -= 3;
	}
	return (mesh);
}

static void	register_line(char *line, t_datas *datas)
{
	int	i;
	int len_format;

	i = 0;
	while (i < 2)
	{
		len_format = ft_strlen(g_registers[i].format);
		if (!ft_strncmp(line, g_registers[i].format, len_format))
		{
			g_registers[i].apply(line + len_format, datas);
			break ;
		}
		i++;
	}
}

t_mesh		*load(char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	t_datas	datas;

	ft_bzero(&datas, sizeof(t_datas));
	fd = open(filename, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		register_line(line, &datas);
		ft_strdel(&line);
	}
	if (ret != 0)
		return (NULL);
	ft_strdel(&line);
	return (convert_to_mesh(&datas));
}
