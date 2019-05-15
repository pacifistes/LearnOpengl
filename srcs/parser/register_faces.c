/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_faces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:19:05 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/10 05:10:44 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	register_vertice(char *str, t_datas *datas)
{
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

// static int	is_valid_texture(t_texture *tmp)
// {
// 	if (tmp->u < 0.0 || tmp->v < 0.0 || tmp->w < 0.0 || tmp->u > 0.0 || tmp->v > 0.0 || tmp->w > 0.0)
// 		return (0);
// 	return (1);
// }

// void		register_texture(char *str, t_datas *datas)
// {
// 	t_texture *tmp;
// 	t_texture *temp;

// 	if (str[0] != ' ')
// 		return;
// 	tmp = ft_memalloc(sizeof(t_texture));
// 	if (!tmp)
// 		return ;
// 	if (sscanf(str, " %lf %lf %lf", &tmp->u, &tmp->v, &tmp->w) == 0 || !is_valid_texture(tmp))
// 	{
// 		free(tmp);
// 		tmp = NULL;
// 		return ;
// 	}
// 	temp = datas->textures;
// 	tmp->next = temp;
// 	datas->textures = tmp;
// }

// void	register_normal(char *str, t_datas *datas)
// {
// 	(void)str;
// 	(void)datas;
// }

void	register_face(char *str, t_datas *datas)
{
	t_face	*tmp;
	t_face	*temp;
	int		i;

	if (str[0] != ' ')
		return ;
	tmp = ft_memalloc(sizeof(t_face));
	if (!tmp)
		return ;
	tmp->indices = (t_indice *)malloc(sizeof(t_indice) * 3);
	if (!tmp->indices)
		return ;
	i = 0;
	while (i < 3)
	{
		tmp->indices[i].vertice = -1;
		tmp->indices[i].texture= -1;
		tmp->indices[i].normal = -1;
		i++;
	}
	if (sscanf(str, " %d %d %d", &tmp->indices[0].vertice, &tmp->indices[1].vertice, &tmp->indices[0].vertice) != 3)
	{
		i = 0;
		while (i < 3)
		{
			free(&tmp->indices[i]);
			i++;
		}
		free(tmp);
		tmp = NULL;
		return ;
	}
	if (datas->objects == NULL)
		insert_object(&datas->objects, ft_strdup("undifined"));
	if (datas->objects->groups == NULL)
		insert_group(&datas->objects->groups, ft_strdup("undifined"));
	temp = datas->objects->groups->faces;
	tmp->next = temp;
	datas->objects->groups->faces = tmp;
}
