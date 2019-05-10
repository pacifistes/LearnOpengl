/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/10 05:31:37 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	run(t_datas *datas)
{
	print_datas(datas);
    return ;
}

int		main(int ac, char **args)
{
	t_datas	datas;

	if (ac != 2)
	{
		ft_printf("Usage: ./scop obj_filename\n");
		return (0);
	}
	datas = parse(args[1]);
	if (datas.objects != NULL)
		run(&datas);
	else
		ft_printf("Error in file.");
	return (0);
}
