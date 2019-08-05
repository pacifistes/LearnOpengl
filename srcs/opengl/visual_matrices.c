/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_matrices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:20:37 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/10 17:53:41 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_visual_matrices(t_gl_coordinate_system *v_matrices)
{
	init_matrice(v_matrices->model, 1.0f);
	init_matrice(v_matrices->view, 1.0f);
	init_matrice(v_matrices->projection, 1.0f);
}

void	update_visual_matrices(t_gl_coordinate_system *v_matrices,
t_gl_camera *camera, t_gl_env *env)
{
	init_visual_matrices(v_matrices);
	perspective(v_matrices->projection, 45.0f, WIDTH / HEIGHT);
	look_at(v_matrices->view, camera->pos, vec_add(camera->pos,
	camera->front), camera->up);
	rotate_with_angle(v_matrices->model, new_vector(env->angle_x, env->angle_y, env->angle_z));;
}