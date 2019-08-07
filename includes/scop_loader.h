/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_loader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:08:03 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/07 08:09:07 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_LOADER_H
# define SCOP_LOADER_H

typedef struct	s_mesh
{
	float			*vertices;
	unsigned int	*indices;
	unsigned int	nbr_indices;
	unsigned int	nbr_vertices;
}				t_mesh;

typedef struct	s_indices
{
	int		i_vertices;
	int		i_indices;
}				t_indices;

typedef	struct	s_reader
{
	int		fd;
	int		ret;
	char	*line;
}				t_reader;

t_mesh			*load(char *filename);
void			clear_mesh(t_mesh *mesh);
void			register_vertice(t_mesh *mesh, t_indices *mesh_indices,
float vertice[3]);
void			register_faces(t_mesh *mesh, t_indices *mesh_indices,
int indice[4], int nbr_indice);
void			register_face(t_mesh *mesh, t_indices *mesh_indices,
int indice[3]);
int				load_vertice(char *str, float vertice[3]);
int				load_face(char *str, int indice[4]);

#endif
