/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 08:16:25 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/08 12:12:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int				is_valid_face(t_face *face, unsigned int limit)
{
	int	is_valid;
	int	i;

	is_valid = 1;
	i = 0;
	while (i < 3)
	{
		if (face->indices[i].vertice > limit)
		{
			is_valid = 0;
			break ;
		}
		i++;
	}
	return (is_valid);
}

unsigned int	count_vertices(t_vertice *vertices)
{
	unsigned int nbr;

	nbr = 0;
	while (vertices)
	{
		nbr++;
		vertices = vertices->next;
	}
	return (nbr);
}

unsigned int	count_faces(t_face *faces, unsigned int limit)
{
	unsigned int nbr;

	nbr = 0;
	while (faces)
	{
		if (is_valid_face(faces, limit))
			nbr++;
		faces = faces->next;
	}
	return (nbr);
}

void			clear_datas_continue(t_datas *datas)
{
	t_datas tmp;

	while (datas->normals)
	{
		tmp.normals = datas->normals;
		datas->normals = datas->normals->next;
		free(tmp.normals);
	}
	while (datas->textures)
	{
		tmp.textures = datas->textures;
		datas->textures = datas->textures->next;
		free(tmp.textures);
	}
}

void			clear_datas(t_datas *datas)
{
	t_datas tmp;

	while (datas->faces)
	{
		tmp.faces = datas->faces;
		datas->faces = datas->faces->next;
		free(tmp.faces);
	}
	while (datas->vertices)
	{
		tmp.vertices = datas->vertices;
		datas->vertices = datas->vertices->next;
		free(tmp.vertices);
	}
	clear_datas_continue(datas);
}
