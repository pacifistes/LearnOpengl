/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/31 17:14:30 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	set_matrice(GLuint shader, char *str, GLfloat *matrice)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrice);
}

void	set_vector(GLuint shader, char *str, t_vector vector)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void	set_int(GLuint shader, char *str, int value)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniform1i(location, value);
}

void	set_float(GLuint shader, char *str, float value)
{
	GLint location = glGetUniformLocation(shader, str);
	glUniform1f(location, value);
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

	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
		tmp->light_pos = vec_sub(tmp->light_pos, new_vector(0.0f, 0.0f, 0.1f));
	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
		tmp->light_pos = vec_add(tmp->light_pos, new_vector(0.0f, 0.0f, 0.1f));
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
		tmp->light_pos = vec_sub(tmp->light_pos, new_vector(0.1f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
		tmp->light_pos = vec_add(tmp->light_pos, new_vector(0.1f, 0.0f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
		tmp->light_pos = vec_add(tmp->light_pos, new_vector(0.0f, 0.1f, 0.0f));
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
		tmp->light_pos = vec_sub(tmp->light_pos, new_vector(0.0f, 0.1f, 0.0f));

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
	tmp.camera_pos = new_vector(0.0f, 0.0f, -0.0f);
	tmp.camera_front = new_vector(0.0f, 0.0f, -1.0f);
	tmp.camera_up = new_vector(0.0f, 1.0f, 0.0f);
	tmp.light_pos = new_vector(1.2f, 1.0f, 2.0f);
	// glUseProgram(opengl->shader);
	// glUniform1i(glGetUniformLocation(opengl->shader, "texture1"), 0);
	// glUniform1i(glGetUniformLocation(opengl->shader, "texture2"), 1);
	// glUniformMatrix4fv(glGetUniformLocation(opengl->shader, "transform"), 1, GL_FALSE, tmp.matrice);
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


	t_vector pointLightPositions[] = {
		new_vector(0.7f, 0.2f, 0.2f),
		new_vector(2.3f,  -3.3f, -4.0f),
		new_vector(-4.0f,  2.0f, 12.0f),
		new_vector(0.0f,  0.0f, -3.0f)
	};
	set_int(opengl->light_shader, "material.diffuse", 0);
	set_int(opengl->light_shader, "material.specular", 1);
	while (!glfwWindowShouldClose(opengl->window))
	{
		current_frame = glfwGetTime();
		tmp.delta_time = current_frame - tmp.last_frame;
		tmp.last_frame = current_frame;

		processKeyInput(opengl->window, &tmp);
		processMouseInput(opengl->window, &tmp);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		init_matrice(tmp.model, 1.0f);
		init_matrice(tmp.view, 1.0f);
		init_matrice(tmp.projection, 1.0f);
		perspective(tmp.projection, tmp.fov, WIDTH / HEIGHT);
		look_at(tmp.view, tmp.camera_pos, vec_add(tmp.camera_pos, tmp.camera_front), tmp.camera_up);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, opengl->texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, opengl->texture2);
		glUseProgram(opengl->shader);

		glUseProgram(opengl->light_shader);
		set_vector(opengl->light_shader, "viewPos", tmp.camera_pos);
		set_float(opengl->light_shader, "material.shininess", 32.0f);
		set_matrice(opengl->light_shader, "model", tmp.model);
		set_matrice(opengl->light_shader, "view", tmp.view);
		set_matrice(opengl->light_shader, "projection", tmp.projection);

		 // directional light
        set_vector(opengl->light_shader, "dirLight.direction", new_vector(-0.2f, -1.0f, -0.3f));
        set_vector(opengl->light_shader, "dirLight.ambient", new_vector(0.05f, 0.05f, 0.05f));
        set_vector(opengl->light_shader, "dirLight.diffuse", new_vector(0.4f, 0.4f, 0.4f));
        set_vector(opengl->light_shader, "dirLight.specular", new_vector(0.5f, 0.5f, 0.5f));
        // point light 1
        set_vector(opengl->light_shader, "pointLights[0].position", pointLightPositions[0]);
        set_vector(opengl->light_shader, "pointLights[0].ambient", new_vector(0.05f, 0.05f, 0.05f));
        set_vector(opengl->light_shader, "pointLights[0].diffuse", new_vector(0.8f, 0.8f, 0.8f));
        set_vector(opengl->light_shader, "pointLights[0].specular", new_vector(1.0f, 1.0f, 1.0f));
        set_float(opengl->light_shader, "pointLights[0].constant", 1.0f);
        set_float(opengl->light_shader, "pointLights[0].linear", 0.09);
        set_float(opengl->light_shader, "pointLights[0].quadratic", 0.032);
        // point light 2
        set_vector(opengl->light_shader, "pointLights[1].position", pointLightPositions[1]);
        set_vector(opengl->light_shader, "pointLights[1].ambient", new_vector(0.05f, 0.05f, 0.05f));
        set_vector(opengl->light_shader, "pointLights[1].diffuse", new_vector(0.8f, 0.8f, 0.8f));
        set_vector(opengl->light_shader, "pointLights[1].specular", new_vector(1.0f, 1.0f, 1.0f));
        set_float(opengl->light_shader, "pointLights[1].constant", 1.0f);
        set_float(opengl->light_shader, "pointLights[1].linear", 0.09);
        set_float(opengl->light_shader, "pointLights[1].quadratic", 0.032);
        // point light 3
        set_vector(opengl->light_shader, "pointLights[2].position", pointLightPositions[2]);
        set_vector(opengl->light_shader, "pointLights[2].ambient", new_vector(0.05f, 0.05f, 0.05f));
        set_vector(opengl->light_shader, "pointLights[2].diffuse", new_vector(0.8f, 0.8f, 0.8f));
        set_vector(opengl->light_shader, "pointLights[2].specular", new_vector(1.0f, 1.0f, 1.0f));
        set_float(opengl->light_shader, "pointLights[2].constant", 1.0f);
        set_float(opengl->light_shader, "pointLights[2].linear", 0.09);
        set_float(opengl->light_shader, "pointLights[2].quadratic", 0.032);
        // point light 4
        set_vector(opengl->light_shader, "pointLights[3].position", pointLightPositions[3]);
        set_vector(opengl->light_shader, "pointLights[3].ambient", new_vector(0.05f, 0.05f, 0.05f));
        set_vector(opengl->light_shader, "pointLights[3].diffuse", new_vector(0.8f, 0.8f, 0.8f));
        set_vector(opengl->light_shader, "pointLights[3].specular", new_vector(1.0f, 1.0f, 1.0f));
        set_float(opengl->light_shader, "pointLights[3].constant", 1.0f);
        set_float(opengl->light_shader, "pointLights[3].linear", 0.09);
        set_float(opengl->light_shader, "pointLights[3].quadratic", 0.032);
        // spotLight
        set_vector(opengl->light_shader, "spotLight.position", tmp.camera_pos);
        set_vector(opengl->light_shader, "spotLight.direction", tmp.camera_front);
        set_vector(opengl->light_shader, "spotLight.ambient", new_vector(0.0f, 0.0f, 0.0f));
        set_vector(opengl->light_shader, "spotLight.diffuse", new_vector(1.0f, 1.0f, 1.0f));
        set_vector(opengl->light_shader, "spotLight.specular", new_vector(1.0f, 1.0f, 1.0f));
        set_float(opengl->light_shader, "spotLight.constant", 1.0f);
        set_float(opengl->light_shader, "spotLight.linear", 0.09);
        set_float(opengl->light_shader, "spotLight.quadratic", 0.032);
        set_float(opengl->light_shader, "spotLight.cutOff", cos(12.5f * DEG_TO_RAD));
        set_float(opengl->light_shader, "spotLight.outerCutOff", cos(15.0f * DEG_TO_RAD));
		

		glBindVertexArray(opengl->cube_vao);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
		for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            init_matrice(tmp.model, 1.0f);
            translate(tmp.model, cubePositions[i]);
            float angle = 20.0f * i;
            rotate_with_axis(tmp.model, angle, new_vector(1.0f, 0.3f, 0.5f));
			set_matrice(opengl->light_shader, "model", tmp.model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }




		glUseProgram(opengl->lamp_shader);	
		set_matrice(opengl->lamp_shader, "view", tmp.view);
		set_matrice(opengl->lamp_shader, "projection", tmp.projection);
        glBindVertexArray(opengl->light_vao);
		for (unsigned int i = 0; i < 4; i++)
		{
			init_matrice(tmp.model, 1.0f);
			translate(tmp.model, pointLightPositions[i]);
			set_matrice(opengl->lamp_shader, "model", tmp.model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);
		glfwSwapBuffers(opengl->window);
		glfwPollEvents();
		tmp.angle = fmodf(tmp.angle + 0.1, 360.f);
	}
}

void	run(t_datas *datas)
{
	t_opengl opengl;
// "./shaders/shader.vs"
// "./shaders/shader.fs"

	(void)datas;
	opengl.window = init_window();
	opengl.light_shader = init_shader("./shaders/multiple_light.vs", "./shaders/multiple_light.fs");
	opengl.lamp_shader = init_shader("./shaders/lamp.vs", "./shaders/lamp.fs");
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
