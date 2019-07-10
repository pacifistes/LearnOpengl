/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:54:22 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/10 17:26:42 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_math.h"

t_vector	normalize(t_vector v)
{
	double		norm;
	t_vector	result;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (norm)
	{
		result.x = v.x / norm;
		result.y = v.y / norm;
		result.z = v.z / norm;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector new_vec;

	new_vec.x = v1.x - v2.x;
	new_vec.y = v1.y - v2.y;
	new_vec.z = v1.z - v2.z;
	return (new_vec);
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector new_vec;

	new_vec.x = v1.x + v2.x;
	new_vec.y = v1.y + v2.y;
	new_vec.z = v1.z + v2.z;
	return (new_vec);
}

t_vector	new_vector(float x, float y, float z)
{
	t_vector new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

float		dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
