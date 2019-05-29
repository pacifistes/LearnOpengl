/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/28 20:11:22 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_matrice(GLuint shader, char *str, GLfloat *matrice)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrice);
}

void	print_matrice(float matrice[16])
{
	int i;

	i = 0;
	while (i < 4)
	{
		printf("[%lf, %lf, %lf, %lf]\n", matrice[i * 4], matrice[i * 4 + 1],
		matrice[i * 4 + 2], matrice[i * 4 + 3]);
		i++;
	}
}

void processKeyInput(GLFWwindow *window, t_tmp *tmp)
{
	float camera_speed;

	camera_speed = 10.0f * tmp->delta_time;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		tmp->camera_pos = vec_add(tmp->camera_pos, scale(tmp->camera_front, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		tmp->camera_pos = vec_sub(tmp->camera_pos, scale(tmp->camera_front, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		tmp->camera_pos = vec_sub(tmp->camera_pos, scale(normalize(cross(tmp->camera_front, tmp->camera_up)), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		tmp->camera_pos = vec_add(tmp->camera_pos, scale(normalize(cross(tmp->camera_front, tmp->camera_up)), camera_speed));
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		tmp->camera_pos = vec_sub(tmp->camera_pos, scale(tmp->camera_up, camera_speed));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		tmp->camera_pos = vec_add(tmp->camera_pos, scale(tmp->camera_up, camera_speed));
}

void processMouseInput(GLFWwindow *window, t_tmp *tmp)
{
	static int	firstMouse = 1;
	double		x_pos;
	double		y_pos;
	double		xoffset;
	double		yoffset;
	double		sensitivity;
	t_vector front;

	glfwGetCursorPos(window, &x_pos, &y_pos);
	if (firstMouse)
	{
		tmp->last_x = x_pos;
		tmp->last_y = y_pos;
		firstMouse = 0;
	}
	xoffset = x_pos - tmp->last_x;
	yoffset = tmp->last_y - y_pos;
	tmp->last_x = x_pos;
	tmp->last_y = y_pos;

	sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	tmp->yaw += xoffset;
	tmp->pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (tmp->pitch > 89.0f)
		tmp->pitch = 89.0f;
	if (tmp->pitch < -89.0f)
		tmp->pitch = -89.0f;

	front.x = cos(tmp->yaw * DEG_TO_RAD) * cos(tmp->pitch * DEG_TO_RAD);
	front.y = sin(tmp->pitch * DEG_TO_RAD);
	front.z = sin(tmp->yaw * DEG_TO_RAD) * cos(tmp->pitch * DEG_TO_RAD);
	tmp->camera_front = normalize(front);
}


void	loop(t_opengl *opengl)
{
	t_tmp	tmp;
	float 	current_frame;
	
	tmp.angle = 0.0f;
	init_matrice(tmp.matrice, 1.0f);
	tmp.camera_pos = new_vector(0.0f, 0.0f, 0.0f);
	tmp.camera_front = new_vector(0.0f, 0.0f, -1.0f);
	tmp.camera_up = new_vector(0.0f, 1.0f, 0.0f);
	glUseProgram(opengl->shader);
	glUniform1i(glGetUniformLocation(opengl->shader, "texture1"), 0);
	glUniform1i(glGetUniformLocation(opengl->shader, "texture2"), 1);
	glUniformMatrix4fv(glGetUniformLocation(opengl->shader, "transform"), 1, GL_FALSE, tmp.matrice);
	//For key
	tmp.delta_time = 0.0f;
	tmp.last_frame = 0.0f;
	//Mouse
	tmp.yaw   = -90.0f;
	tmp.pitch =  0.0f;
	tmp.last_x =  WIDTH / 2.0f;
	tmp.last_y =  HEIGHT / 2.0f;
	tmp.fov   =  45.0f;

	t_vector cubePositions[] = {
		new_vector( 0.0f,  0.0f,  0.0f),
		new_vector( 2.0f,  5.0f, -15.0f),
		new_vector(-1.5f, -2.2f, -2.5f),
		new_vector(-3.8f, -2.0f, -12.3f),
		new_vector( 2.4f, -0.4f, -3.5f),
		new_vector(-1.7f,  3.0f, -7.5f),
		new_vector( 1.3f, -2.0f, -2.5f),
		new_vector( 1.5f,  2.0f, -2.5f),
		new_vector( 1.5f,  0.2f, -1.5f),
		new_vector(-1.3f,  1.0f, -1.5f)
	};
	while (!glfwWindowShouldClose(opengl->window))
	{
		current_frame = glfwGetTime();
		tmp.delta_time = current_frame - tmp.last_frame;
		tmp.last_frame = current_frame;

		processKeyInput(opengl->window, &tmp);
		processMouseInput(opengl->window, &tmp);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, opengl->texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, opengl->texture2);
		glUseProgram(opengl->shader);

		init_matrice(tmp.model, 1.0f);
		init_matrice(tmp.view, 1.0f);
		init_matrice(tmp.projection, 1.0f);

		perspective(tmp.projection, tmp.fov, WIDTH / HEIGHT);
		// print_matrice(tmp.model);
		// exit(1);
		// translate(tmp.view, new_vector(0.0f, 0.0f, -3.0f));
		look_at(tmp.view, tmp.camera_pos, vec_add(tmp.camera_pos, tmp.camera_front), tmp.camera_up);
		set_matrice(opengl->shader, "model", tmp.model);
		set_matrice(opengl->shader, "view", tmp.view);
		set_matrice(opengl->shader, "projection", tmp.projection);

		glBindVertexArray(opengl->vao);
		for (unsigned int i = 0; i < 10; i++)
		{
			translate(tmp.model, cubePositions[i]);
			float angle = 20.0f * i;
			rotate_with_axis(tmp.model, 100 * (angle + glfwGetTime()), new_vector(1.0f, 0.3f, 0.5f));
			set_matrice(opengl->shader, "model", tmp.model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// glDrawArrays(GL_TRIANGLES, 0, 36);//TO DELETE
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // NUMBERS OF INDIC

		glBindVertexArray(0);
		glfwSwapBuffers(opengl->window);
		glfwPollEvents();
		tmp.angle = fmodf(tmp.angle + 0.1, 360.f);
	}
}


void	run(t_datas *datas)
{
	t_opengl opengl;

	(void)datas;
	opengl.window = init_window();
	opengl.shader = init_shader();
	init_buffers(&opengl);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_LINE || GL_FILL
	init_textures(&opengl);
	loop(&opengl);
	clear_ressources(&opengl.vao, &opengl.vbo, &opengl.ebo);
	return ;
}

int		main(int ac, char **args)
{
	t_datas	datas;

	if (ac != 2)
	{
		ft_printf("Usage: ./scop obj_filename\n");
		return (0);
	}
	datas = parse(args[1]);
	if (datas.objects != NULL)
		run(&datas);
	else
		ft_printf("Error in file.");
	return (0);
}
