/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:44:36 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/09 15:30:59 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_tools(t_gl_tools *tools)
{
	tools->angle = 0.0f;
	tools->delta_time = 0.0f;
	tools->last_frame = 0.0f;
	tools->yaw  = -90.0f;
	tools->pitch = 0.0f;
	tools->last_x = WIDTH / 2.0f;
	tools->last_y = HEIGHT / 2.0f;
}

void	update_tools(t_gl_tools *tools)
{
	float current_frame;

	current_frame = glfwGetTime();
	tools->delta_time = current_frame - tools->last_frame;
	tools->last_frame = current_frame;
	tools->angle = fmodf(tools->angle + 0.1, 360.f);
}