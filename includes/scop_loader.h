/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:08:03 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/05 04:29:46 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_LOADER_H
# define SCOP_LOADER_H

typedef struct	s_vertice
{
	double	x;
	double	y;
	double	z;
	void	*next;
}				t_vertice;

typedef struct	s_texture
{
	double	u;
	double	v;
	double	w;
	void	*next;
}				t_texture;

typedef struct	s_normal
{
	double	x;
	double	y;
	double	z;
	void	*next;
}				t_normal;

typedef	struct	s_indice
{
	uint32_t	vertice;
	uint32_t	texture;
	uint32_t	normal;
}				t_indice;

typedef	struct	s_face
{
	t_indice	indices[3];
	void		*next;
}				t_face;

typedef struct	s_datas
{
	t_face		*faces;
	t_vertice	*vertices;
	t_texture	*textures;
	t_normal	*normals;
}				t_datas;

typedef struct	s_mesh
{
	float			*vertices;
	unsigned int	*indices;
	unsigned int	nbr_indices;
	unsigned int	nbr_vertices;
}				t_mesh;

typedef struct	s_register
{
	char	*format;
	void	(*apply)(char *line, t_datas *datas);
}				t_register;

t_mesh			*load(char *filename);
void			register_vertice(char *str, t_datas *datas);
void			register_face(char *str, t_datas *datas);
void			print_datas(t_datas *datas);
void			clear_datas(t_datas *datas);
void			clear_mesh(t_mesh *mesh);

#endif
