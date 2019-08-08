/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 04:52:13 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/08 12:18:33 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	register_line(char *line, t_datas *datas)
{
	static const t_register registers[] = {
		{"v", &register_vertice},
		{"f", &register_face}
	};
	int						i;
	int						len_format;

	i = 0;
	while (i < 2)
	{
		len_format = ft_strlen(registers[i].format);
		if (!ft_strncmp(line, registers[i].format, len_format))
		{
			registers[i].apply(line + len_format, datas);
			break ;
		}
		i++;
	}
}

t_mesh		*load(char *filename)
{
	t_reader	reader;
	t_datas		datas;
	t_mesh		*mesh;

	ft_bzero(&datas, sizeof(t_datas));
	reader.fd = open(filename, O_RDONLY);
	while ((reader.ret = get_next_line(reader.fd, &reader.line)) > 0)
	{
		register_line(reader.line, &datas);
		ft_strdel(&reader.line);
	}
	if (reader.ret != 0)
		return (NULL);
	ft_strdel(&reader.line);
	mesh = convert_to_mesh(&datas);
	align_mesh(mesh);
	clear_datas(&datas);
	return (mesh);
}
