/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_systems.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:20:37 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/09 16:10:41 by bbrunell         ###   ########.fr       */
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
	rotate_with_axis(c_systems->model, angle, new_vector(0.0f, 1.0f, 0.0f));
}

void	send_coordinate_systems(t_gl_coordinate_system *c_systems, GLuint shader)
{
	set_matrice(shader, "model", c_systems->model);
	set_matrice(shader, "view", c_systems->view);
	set_matrice(shader, "projection", c_systems->projection);
}
