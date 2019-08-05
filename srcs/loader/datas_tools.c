/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:39:42 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/03 00:48:09 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	print_datas(t_datas *datas)
{
	(void)datas;
	while (datas->vertices)
	{
		printf("v %f %f %f\n", datas->vertices->x, datas->vertices->y, datas->vertices->z);
		datas->vertices = datas->vertices->next;
	}
	while (datas->faces)
	{
		printf("f %u/%u/%u", datas->faces->indices[0].vertice, datas->faces->indices[0].texture, datas->faces->indices[0].normal);
		printf(" %u/%u/%u", datas->faces->indices[1].vertice, datas->faces->indices[1].texture, datas->faces->indices[1].normal);
		printf(" %u/%u/%u\n", datas->faces->indices[2].vertice, datas->faces->indices[2].texture, datas->faces->indices[2].normal);
		datas->faces = datas->faces->next;
	}
}

void	clear_datas(t_datas *datas)
{
	(void)datas;
}