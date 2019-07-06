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

static int	is_valid_obj(t_datas *datas)
{
	(void)datas;
	return (0);
}

static void	register_line(char *line, t_datas *datas)
{
	int	i;
	int len_format;

	i = 0;
	while (i < 4)
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
	if (!is_valid_obj(&datas))
		clear_datas(&datas);
	return (NULL);//Convert To mesh
}
