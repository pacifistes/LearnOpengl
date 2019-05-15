/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datas_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 00:39:42 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/10 04:18:02 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	insert_object(t_object **objects, char *name)
{
	t_object *tmp;
	t_object *temp;

	tmp = ft_memalloc(sizeof(t_object));
	if (!tmp)
		return ;
	tmp->name = name;
	temp = *objects;
	tmp->next = temp;
	*objects = tmp;
}

void	insert_group(t_group **groups, char *name)
{
	t_group *tmp;
	t_group *temp;

	tmp = ft_memalloc(sizeof(t_group));
	if (!tmp)
		return ;
	tmp->name = name;
	temp = *groups;
	tmp->next = temp;
	*groups = tmp;
}

void	print_datas(t_datas *datas)
{
	ft_printf("objects:\n");
	while (datas->objects)
	{
		ft_printf("\t%s\n", datas->objects->name);
		ft_printf("\tgroups:\n");
		while (datas->objects->groups)
		{
			ft_printf("\t\t%s\n", datas->objects->groups->name);
			datas->objects->groups = datas->objects->groups->next;
		}
		datas->objects = datas->objects->next;
	}
}

void	clear_datas(t_datas *datas)
{
	(void)datas;
}