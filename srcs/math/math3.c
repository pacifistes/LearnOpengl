/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:22:43 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/05 03:12:49 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


void	rotate_x(float matrice[16], float angle)
{
	float cosinus;
	float sinus;

	if (angle == 0.0f)
		return;
	angle *= DEG_TO_RAD;
	cosinus = cos(angle);
	sinus = sin(angle);
	matrice[5] = cosinus;
	matrice[9] = -sinus;
	matrice[6] = sinus;
	matrice[10] = cosinus;
}

void	rotate_y(float matrice[16], float angle)
{
	float cosinus;
	float sinus;

	if (angle == 0.0f)
		return;
	angle *= DEG_TO_RAD;
	cosinus = cos(angle);
	sinus = sin(angle);
	matrice[0] = cosinus;
	matrice[8] = sinus;
	matrice[2] = -sinus;
	matrice[10] = cosinus;
}

void	rotate_z(float matrice[16], float angle)
{
	float cosinus;
	float sinus;

	if (angle == 0.0f)
		return;
	angle *= DEG_TO_RAD;
	cosinus = cos(angle);
	sinus = sin(angle);
	matrice[0] = cosinus;
	matrice[4] = -sinus;
	matrice[1] = sinus;
	matrice[5] = cosinus;
}

void	rotate_with_angle(float matrice[16], t_vector angles)
{
	t_vector s;
	t_vector c;
	
	angles.x *= DEG_TO_RAD;
	angles.y *= DEG_TO_RAD;
	angles.z *= DEG_TO_RAD;
	s.x = sin(angles.x);
	s.y = sin(angles.y);
	s.z = sin(angles.z);
	c.x = cos(angles.x);
	c.y = cos(angles.y);
	c.z = cos(angles.z);
	matrice[0] = c.y * c.z;
	matrice[4] = s.x * s.y * c.z + c.x * s.z;
	matrice[8] = (-c.x) * s.y * c.z + s.x * s.z;
	matrice[1] = (-c.y) * s.z;
	matrice[5] = (-s.x) * s.y * s.z + c.x * c.z;
	matrice[9] = c.x * s.y * s.z + s.x * c.z;
	matrice[2] = s.y;
	matrice[6] = (-s.x) * c.y;
	matrice[10] = c.x * c.y;
}

void	rotate_with_axis(float matrice[16], float angle, t_vector axis)
{
	float		cosinus;
	float		sinus;
	float		constant;
	t_vector	tmp;

	angle *= DEG_TO_RAD;
	cosinus = cos(angle);
	sinus = sin(angle);
	axis = normalize(axis);
	constant = 1 - cosinus;
	tmp.x = axis.x * constant;
	tmp.y = axis.y * constant;
	tmp.z = axis.z * constant;
	matrice[0] = cosinus + tmp.x * axis.x;
	matrice[4] = tmp.x * axis.y + sinus * axis.z;
	matrice[8] = tmp.x * axis.z - sinus * axis.y;
	matrice[1] = tmp.y * axis.x - sinus * axis.z;
	matrice[5] = cosinus + tmp.y * axis.y;
	matrice[9] = tmp.y * axis.z + sinus * axis.x;
	matrice[2] = tmp.z * axis.x + sinus * axis.y;
	matrice[6] = tmp.z * axis.y - sinus * axis.x;
	matrice[10] = cosinus + tmp.z * axis.z;
}
