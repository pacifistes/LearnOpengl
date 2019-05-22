/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:54:08 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/22 17:55:06 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_math.h"

void	init_matrice(float matrice[16], float value)
{
	ft_bzero(matrice, sizeof(float) * 16);
	matrice[0] = value;
	matrice[5] = value;
	matrice[10] = value;
	matrice[15] = value;
}

// void	perspective(float matrice[16], float fov, float aspect)
// {
// 	float tan_half_fov;
// 	float z_near;
// 	float z_far;
// 	float z_range;
// 	float angle;


// 	angle = fov * DEG_TO_RAD;
// 	z_near = 0.1f;
// 	z_far = 100.0f;
// 	z_range = z_far - z_near;

// 	init_matrice(matrice, 1.0f);
// 	tan_half_fov = tan(angle * 0.5);
// 	matrice[0] =  tan_half_fov / aspect;
// 	matrice[5] = fmodf(1, tan_half_fov);
// 	matrice[10] = fmodf(-z_far, z_range);
// 	matrice[11] = -1;
// 	matrice[14] = fmodf(-(z_far * z_near), z_range);
// 	matrice[15] = 0;
// }

void	perspective(float matrice[16], float fov, float aspect)
{
	float tan_half_fov;
	float z_near;
	float z_far;
	float z_range;
	float angle;


	angle = fov * DEG_TO_RAD;
	z_near = 0.1f;
	z_far = 100.0f;
	z_range = z_far - z_near;

	init_matrice(matrice, 1.0f);
	tan_half_fov = tan(angle * 0.5);
	matrice[0] = fmodf(1, aspect * tan_half_fov);
	matrice[5] = fmodf(1, tan_half_fov);
	matrice[10] = -fmodf(z_near - z_far, z_range);
	matrice[11] = 1;
	matrice[14] = fmodf(2 * z_far * z_near, z_range);
	matrice[15] = 0;
}

void	translate(float matrice[16], t_vector vector)
{
	matrice[12] = vector.x;
	matrice[13] = vector.y;
	matrice[14] = vector.z;
}

void		look_at(float matrice[16], t_vector eye, t_vector center, t_vector up)
{
	t_vector f;
	t_vector s;
	t_vector u;

	init_matrice(matrice, 1.0f);
	f = normalize(vec_sub(center, eye));
	s = normalize(cross(f, up));
	u = normalize(cross(s, f));
	matrice[0] = s.x;
	matrice[4] = s.y;
	matrice[8] = s.z;
	matrice[1] = u.x;
	matrice[5] = u.y;
	matrice[9] = u.z;
	matrice[2] = -f.x;
	matrice[6] = -f.y;
	matrice[10] = -f.z;
	matrice[12] = -dot(s, eye);
	matrice[13] = -dot(u, eye);
	matrice[14] = dot(f, eye);
}
