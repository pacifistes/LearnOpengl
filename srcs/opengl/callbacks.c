/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:08:57 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/09 15:30:06 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void key_input(GLFWwindow *window, t_gl_camera *camera, float delta_time)
{
	float camera_speed;

	camera_speed = 10.0f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, scale(camera->front, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, scale(camera->front, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, scale(normalize(cross(camera->front, camera->up)), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, scale(normalize(cross(camera->front, camera->up)), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->pos = vec_sub(camera->pos, scale(camera->up, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->pos = vec_add(camera->pos, scale(camera->up, camera_speed));
}

void mouse_input(GLFWwindow *window, t_gl_camera *camera, t_gl_tools *tools)
{
	static int	first_mouse = 1;
	double		x_pos;
	double		y_pos;
	t_vector front;

	glfwGetCursorPos(window, &x_pos, &y_pos);
	if (first_mouse)
	{
		tools->last_x = x_pos;
		tools->last_y = y_pos;
		first_mouse = 0;
	}
	tools->yaw += (x_pos - tools->last_x) * 0.1f;
	tools->pitch += (tools->last_y - y_pos) * 0.1f;
	tools->last_x = x_pos;
	tools->last_y = y_pos;
	if (tools->pitch > 89.0f)
		tools->pitch = 89.0f;
	if (tools->pitch < -89.0f)
		tools->pitch = -89.0f;
	front.x = cos(tools->yaw * DEG_TO_RAD) * cos(tools->pitch * DEG_TO_RAD);
	front.y = sin(tools->pitch * DEG_TO_RAD);
	front.z = sin(tools->yaw * DEG_TO_RAD) * cos(tools->pitch * DEG_TO_RAD);
	camera->front = normalize(front);
}
