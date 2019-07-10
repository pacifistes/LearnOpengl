/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:28:33 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/10 17:28:41 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_math.h"

t_vector	scale(t_vector v1, float value)
{
	t_vector v_scale;

	v_scale.x = v1.x * value;
	v_scale.y = v1.y * value;
	v_scale.z = v1.z * value;
	return (v_scale);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}
