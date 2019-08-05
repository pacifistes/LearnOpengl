/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_math.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:29:29 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/05 02:47:15 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_MATH_H
# define SCOP_MATH_H

# include "ft_printf.h"
# include <math.h>

# define PI 3.14159265359
# define RAD_TO_DEG (180.0 / PI)
# define DEG_TO_RAD (PI / 180.0)

typedef struct	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

t_vector		normalize(t_vector v);
t_vector		cross(t_vector v1, t_vector v2);
float			dot(t_vector v1, t_vector v2);
void			init_matrice(float matrice[16], float value);
void			look_at(float matrice[16], t_vector eye, t_vector center,
t_vector up);
t_vector		new_vector(float x, float y, float z);
void			perspective(float matrice[16], float fov, float aspect);
void			perspective2(float matrice[16], float fov, float aspect,
float width, float height);
void			rotate_with_axis(float matrice[16], float angle, t_vector axis);
void	rotate_with_angle(float matrice[16], t_vector angles);
void			rotate_x(float matrice[16], float angle);
void			rotate_y(float matrice[16], float angle);
void			rotate_z(float matrice[16], float angle);
t_vector		scale(t_vector v1, float value);
void			translate(float matrice[16], t_vector vector);
t_vector		vec_sub(t_vector v1, t_vector v2);
t_vector		vec_add(t_vector v1, t_vector v2);
void			print_matrice(float matrice[16]);

#endif
