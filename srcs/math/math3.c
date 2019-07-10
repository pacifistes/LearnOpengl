/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:22:43 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/09 19:33:53 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	rotate_x(float matrice[16], float angle)
{
	float cosinus;
	float sinus;

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

	angle *= DEG_TO_RAD;
	cosinus = cos(angle);
	sinus = sin(angle);
	matrice[0] = cosinus;
	matrice[4] = -sinus;
	matrice[1] = sinus;
	matrice[5] = cosinus;
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
