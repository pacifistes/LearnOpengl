/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_faces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:19:05 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/03 03:09:43 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	register_vertice(char *str, t_datas *datas)
{
	(void)datas;
	(void)str;
	t_vertice	*tmp;
	t_vertice	*temp;

	if (str[0] != ' ')
		return ;
	tmp = ft_memalloc(sizeof(t_vertice));
	if (!tmp)
		return ;
	tmp->w = 1.0;
	if (sscanf(str, " %lf %lf %lf %lf", &tmp->x, &tmp->y, &tmp->z, &tmp->w)< 3)
	{
		free(tmp);
		tmp = NULL;
		return ;
	}
	temp = datas->vertices;
	tmp->next = temp;
	datas->vertices = tmp;
}

void		register_texture(char *str, t_datas *datas)
{
	(void)str;
	(void)datas;
	// t_texture *tmp;
	// t_texture *temp;

	// if (str[0] != ' ')
	// 	return;
	// tmp = ft_memalloc(sizeof(t_texture));
	// if (!tmp)
	// 	return ;
	// if (sscanf(str, " %lf %lf %lf", &tmp->u, &tmp->v, &tmp->w) == 0 || !is_valid_texture(tmp))
	// {
	// 	free(tmp);
	// 	tmp = NULL;
	// 	return ;
	// }
	// temp = datas->textures;
	// tmp->next = temp;
	// datas->textures = tmp;
}

void	register_normal(char *str, t_datas *datas)
{
	(void)str;
	(void)datas;
}

void	add_face(t_datas *datas, t_face face)
{
	t_face	*tmp;
	t_face	*temp;

	tmp = ft_memalloc(sizeof(t_face));
	ft_memcpy(tmp, &face, sizeof(face));
	if (!tmp)
		return ;
	temp = datas->faces;
	tmp->next = temp;
	datas->faces = tmp;
}

void	register_face(char *str, t_datas *datas)
{
	t_indice	indices[4];
	t_face		face;
	int			nbr_success;

	ft_bzero(indices, sizeof(t_indice) * 4);
	nbr_success = sscanf(str, " %d %d %d %d", &indices[0].vertice,
	&indices[1].vertice, &indices[2].vertice, &indices[3].vertice);
	if (nbr_success < 3)
		return;
	if (nbr_success == 3)
	{
		face.indices[0] = indices[0];
		face.indices[1] = indices[1];
		face.indices[2] = indices[2];
		add_face(datas, face);
	}
	else if (nbr_success == 4)
	{
		face.indices[0] = indices[0];
		face.indices[1] = indices[1];
		face.indices[2] = indices[3];
		add_face(datas, face);
		face.indices[0] = indices[1];
		face.indices[1] = indices[2];
		face.indices[2] = indices[3];
		add_face(datas, face);
	}
}
