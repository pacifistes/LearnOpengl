/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_names.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:19:10 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/10 01:16:37 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	register_group_name(char *str, t_datas *datas)
{
	char *name;

	if (str[0] != ' ')
		return;
	name = ft_strtrim(str);
	if (datas->objects == NULL)
		insert_object(&datas->objects, ft_strdup("undifined"));
	if (name == NULL)
		insert_group(&datas->objects->groups, ft_strdup("undifined"));
	else
		insert_group(&datas->objects->groups, name);
}

void	register_object_name(char *str, t_datas *datas)
{
	char *name;

	if (str[0] != ' ')
		return;
	name = ft_strtrim(str);
	if (name == NULL)
		insert_object(&datas->objects, ft_strdup("undifined"));
	else
		insert_object(&datas->objects, name);
}
