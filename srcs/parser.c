/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:21:55 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/05 19:55:19 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int is_valid_obj()
{
	
}

int parse(char *filename)
{
	int 	fd;
	int		ret;
	char	*line;

	fd = open(filename, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
			
	}
	if (ret != 0)
		ft_printf("Error file\n");
	return (0);
}