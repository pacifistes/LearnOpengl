/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:54:08 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/10 17:25:25 by bbrunell         ###   ########.fr       */
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

void	print_matrice(float matrice[16])
{
	int i;

	i = 0;
	while (i < 4)
	{
		printf("[%lf, %lf, %lf, %lf]\n", matrice[i * 4], matrice[i * 4 + 1],
		matrice[i * 4 + 2], matrice[i * 4 + 3]);
		i++;
	}
}

void	perspective(float matrice[16], float fov, float aspect)
{
	float tan_half_fov;
	float z_near;
	float z_far;
	float z_range;
	float height;

	z_near = 0.1f;
	z_far = 100.0f;
	z_range = z_far - z_near;
	init_matrice(matrice, 1.0f);
	tan_half_fov = tan(fov * DEG_TO_RAD * 0.5);
	height = z_near * tan_half_fov;
	matrice[0] = (2.0 * z_near) / ((height * aspect) + (height * aspect));
	matrice[8] = 0;
	matrice[5] = (2.0 * z_near) / (height + height);
	matrice[9] = (height - height) / (height + height);
	matrice[10] = -(z_far + z_near) / z_range;
	matrice[11] = -1;
	matrice[14] = -(2.0f * z_far * z_near) / z_range;
	matrice[15] = 0;
}

void	translate(float matrice[16], t_vector vector)
{
	matrice[12] = vector.x;
	matrice[13] = vector.y;
	matrice[14] = vector.z;
}

void	look_at(float matrice[16], t_vector eye, t_vector center,
t_vector up)
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
