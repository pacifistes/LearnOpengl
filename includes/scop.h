/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:29:29 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/05 19:54:41 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "ft_printf.h"
# include <fcntl.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# define GLFW_DLL

typedef struct	s_coordinate
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_coordinate;

typedef	struct	s_indice {
	uint32_t	vertex;
	uint32_t	texture;
	uint32_t	normal;
}				t_indice;

typedef	struct	s_face {
	t_indice	*indices;
}				t_face;

typedef struct s_object {
	char			*name;
	t_faces			faces;
	t_coordinate	*vertex;
	t_coordinate	*texture;
	t_coordinate	*normal;
}				t_object;

int	parse(char *filename);

#endif

//Vertices
// v: X Y Z W with W optional . Default 1.0

// Texture 
// vt: U V W with [V,W] optional between 0.0-1.0. Default  0.0

// Vertex
// vn: X Y Z

// Face
// f 1 2 3
//   f 3/1 4/2 5/3
//   f 6/4/1 3/5/3 7/6/5
//   f 7//1 8//2 9//3
//   f ...