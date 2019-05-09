/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:29:29 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/09 03:46:43 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "ft_printf.h"
# include <fcntl.h>

# define SIZE_STOCKAGE 50

typedef struct	s_coordinate
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_coordinate;

typedef	struct	s_indice
{
	uint32_t	vertice;
	uint32_t	texture;
	uint32_t	normal;
}				t_indice;

typedef	struct	s_face
{
	t_indice	*indices;
}				t_face;

typedef	struct	s_group
{
	char	*name;
	t_face	*faces;
}				t_group;

typedef struct	s_object
{
	char	*name;
	t_group	*groups;
}				t_object;

typedef struct	s_plop
{
	t_object		*objects;
	t_coordinate	*verices;
	t_coordinate	*textures;
	t_coordinate	*normals;
}				t_plop;

typedef struct	s_register
{
	char	*format;
	void	(*apply)(char *line, t_plop **plop);
}				t_register;

t_plop			*parse(char *filename);
void			register_vertice(char *str, t_plop **plop);
void			register_texture(char *str, t_plop **plop);
void			register_normal(char *str, t_plop **plop);
void			register_face(char *str, t_plop **plop);
void			register_group_name(char *name, t_plop **plop);
void			register_object_name(char *name, t_plop **plop);

static const t_register g_registers[6] = {
	{
		"vn",
		&register_normal
	},
	{
		"vt",
		&register_texture
	},
	{
		"o",
		&register_object_name
	},
	{
		"g",
		&register_group_name
	},
	{
		"v",
		&register_vertice
	},
	{
		"f",
		&register_face
	}
};

#endif

/*
**	Vertices
**	 v: X Y Z W with W optional . Default 1.0
**	 Texture
**	 vt: U V W with [V,W] optional between 0.0-1.0. Default  0.0
**	 Vertex
**	 vn: X Y Z
**	 Face
**	 f 1 2 3
**	   f 3/1 4/2 5/3
**	   f 6/4/1 3/5/3 7/6/5
**	   f 7//1 8//2 9//3
**	   f ...
*/
