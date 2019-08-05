/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:08:57 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/05 05:22:51 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		key_down(GLFWwindow *window, int button)
{
	if (glfwGetKey(window, button) == GLFW_PRESS)
		return (1);
	return (0);
}

int		key_up(GLFWwindow *window, int button, int button_index)
{
	static int keys[] = {
		GLFW_RELEASE,
		GLFW_RELEASE,
		GLFW_RELEASE,
		GLFW_RELEASE
	};
	int		key_press;

	if (button_index > 3)
		return (0);
	key_press = key_down(window, button);
	if (keys[button_index] == GLFW_RELEASE && key_press)
	{
		keys[button_index] = GLFW_PRESS;
		return (1);
	}
	else if (keys[button_index] == GLFW_PRESS && !key_press)
		keys[button_index] = GLFW_RELEASE;
	return (0);
}

void	directional_inputs(GLFWwindow *window, t_gl_camera *camera, float delta_time)
{
	float		camera_speed;

	camera_speed = 10.0f * delta_time;
	if (key_down(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key_down(window, GLFW_KEY_W))
		camera->pos = vec_add(camera->pos, scale(camera->front, camera_speed));
	if (key_down(window, GLFW_KEY_S))
		camera->pos = vec_sub(camera->pos, scale(camera->front, camera_speed));
	if (key_down(window, GLFW_KEY_A))
	{
		camera->pos = vec_sub(camera->pos,
		scale(normalize(cross(camera->front, camera->up)), camera_speed));
	}
	if (key_down(window, GLFW_KEY_D))
	{
		camera->pos = vec_add(camera->pos,
		scale(normalize(cross(camera->front, camera->up)), camera_speed));
	}
	if (key_down(window, GLFW_KEY_Q))
		camera->pos = vec_sub(camera->pos, scale(camera->up, camera_speed));
	if (key_down(window, GLFW_KEY_E))
		camera->pos = vec_add(camera->pos, scale(camera->up, camera_speed));
}

void	rotation_inputs(GLFWwindow *window, t_gl_env *env)
{
	if (key_up(window, GLFW_KEY_KP_7, KEY_7))
		env->rot_x = (env->rot_x) ? 0 : 1;
	if (key_up(window, GLFW_KEY_KP_8, KEY_8))
		env->rot_y = (env->rot_y) ? 0 : 1;
	if (key_up(window, GLFW_KEY_KP_9, KEY_9))
		env->rot_z = (env->rot_z) ? 0 : 1;
}

void	other_inputs(GLFWwindow *window, t_gl_env *env)
{
	if (key_down(window, GLFW_KEY_PAGE_UP))
		env->texture_ratio = fmin(env->texture_ratio + 0.005, 1.0);
	if (key_down(window, GLFW_KEY_PAGE_DOWN))
		env->texture_ratio = fmax(env->texture_ratio - 0.005, 0.0);
	if (key_up(window, GLFW_KEY_C, KEY_C))
		change_polygon_mode();
}

void	mouse_inputs(GLFWwindow *window, t_gl_camera *camera, t_gl_env *env)
{
	static int	first_mouse = 1;
	double		x_pos;
	double		y_pos;
	t_vector	front;

	glfwGetCursorPos(window, &x_pos, &y_pos);
	if (first_mouse)
	{
		env->last_x = x_pos;
		env->last_y = y_pos;
		first_mouse = 0;
	}
	env->yaw += (x_pos - env->last_x) * 0.1f;
	env->pitch += (env->last_y - y_pos) * 0.1f;
	env->last_x = x_pos;
	env->last_y = y_pos;
	if (env->pitch > 89.0f)
		env->pitch = 89.0f;
	if (env->pitch < -89.0f)
		env->pitch = -89.0f;
	front.x = cos(env->yaw * DEG_TO_RAD) * cos(env->pitch * DEG_TO_RAD);
	front.y = sin(env->pitch * DEG_TO_RAD);
	front.z = sin(env->yaw * DEG_TO_RAD) * cos(env->pitch * DEG_TO_RAD);
	camera->front = normalize(front);
}

void	inputs(t_opengl *opengl)
{
	directional_inputs(opengl->window, &opengl->camera, opengl->env.delta_time);
	rotation_inputs(opengl->window, &opengl->env);
	other_inputs(opengl->window, &opengl->env);
	mouse_inputs(opengl->window, &opengl->camera, &opengl->env);
}

