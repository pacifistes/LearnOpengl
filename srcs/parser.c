/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:21:55 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/09 03:53:23 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	is_valid_obj(void)
{
	return (0);
}

static void	register_line(char *line, t_plop **plop)
{
	int	i;
	int len_format;

	i = 0;
	while (i < 6)
	{
		len_format = ft_strlen(g_registers[i].format);
		if (!ft_strncmp(line, g_registers[i].format, len_format))
		{
			g_registers[i].apply(line + len_format, plop);
			break ;
		}
		i++;
	}
}

t_plop		*parse(char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	t_plop	*plop;

	plop = NULL;
	fd = open(filename, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		register_line(line, &plop);
		ft_strdel(&line);
	}
	if (ret != 0)
		return (NULL);
	ft_strdel(&line);
	is_valid_obj();
	return (plop);
}
