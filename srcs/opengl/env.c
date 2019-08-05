/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:44:36 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/04 00:27:54 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_env(t_gl_env *env)
{
	env->angle_x = 0.0f;
	env->angle_y = 0.0f;
	env->angle_z = 0.0f;
	env->rot_x = 0;
	env->rot_y = 1;
	env->rot_z = 0;
	env->delta_time = 0.0f;
	env->last_frame = 0.0f;
	env->yaw = -90.0f;
	env->pitch = 0.0f;
	env->last_x = WIDTH / 2.0f;
	env->last_y = HEIGHT / 2.0f;
}

void	update_env(t_gl_env *env)
{
	float current_frame;

	current_frame = glfwGetTime();
	env->delta_time = current_frame - env->last_frame;
	env->last_frame = current_frame;
	if (env->rot_x)
		env->angle_x = fmodf(env->angle_x + 0.1, 360.f);
	if (env->rot_y)
		env->angle_y = fmodf(env->angle_y + 0.1, 360.f);
	if (env->rot_z)
		env->angle_z = fmodf(env->angle_z + 0.1, 360.f);
}
