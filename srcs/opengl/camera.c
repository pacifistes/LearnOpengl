/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:20:19 by bbrunell          #+#    #+#             */
/*   Updated: 2019/06/13 18:30:31 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_camera(t_gl_camera *camera)
{
	camera->pos = new_vector(0.0f, 0.0f, -0.0f);
	camera->front = new_vector(0.0f, 0.0f, -1.0f);
	camera->up = new_vector(0.0f, 1.0f, 0.0f);
}