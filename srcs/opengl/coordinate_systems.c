/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_systems.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:20:37 by bbrunell          #+#    #+#             */
/*   Updated: 2019/06/25 15:51:45 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_coordinate_systems(t_gl_coordinate_system *c_systems)
{
	init_matrice(c_systems->model, 1.0f);
	init_matrice(c_systems->view, 1.0f);
	init_matrice(c_systems->projection, 1.0f);
}

void	update_coordinate_systems(t_gl_coordinate_system *c_systems,
t_gl_camera *camera, float angle)
{
	perspective(c_systems->projection, 45.0f, WIDTH / HEIGHT);
	look_at(c_systems->view, camera->pos, vec_add(camera->pos,
	camera->front), camera->up);
	// translate(c_systems->model, new_vector(0.0f, 0.0f, -3.0f));
	rotate_with_axis(c_systems->model, angle, new_vector(1.0f, 0.3f, 0.5f));
}
