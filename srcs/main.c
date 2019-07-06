/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/07/06 17:14:54 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


void	loop(t_opengl *opengl, t_mesh *mesh)
{
	for (int i = 0; i < 6; i++) {
		ft_printf("indice = %d\n", mesh->indices[i]);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(opengl->window))
	{
		// update_tools(&opengl->tools);
		key_input(opengl->window, &opengl->camera,
		opengl->tools.delta_time);
		// mouse_input(opengl->window, &opengl->camera, &opengl->tools);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glPolygonMode(GL_FRONT_AND_BACK, opengl->mode);
		// init_coordinate_systems(&opengl->c_systems);
		// update_coordinate_systems(&opengl->c_systems, &opengl->camera, opengl->tools.angle);
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, opengl->textures.texture);
		// glUseProgram(opengl->shaders.shader);
		glUseProgram(opengl->shaders.shader);
		// glBindVertexArray(opengl->buffers.vao);
		glBindVertexArray(opengl->buffers.vao);
		glDrawElements(GL_TRIANGLES, mesh->nbr_indices, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0);
		glfwSwapBuffers(opengl->window);
		glfwPollEvents();
	}
}

void	run(t_mesh *mesh)
{
	t_opengl opengl;

	opengl.window = init_window();
	opengl.shaders.shader = init_shader("./shaders/shader.vs", "./shaders/shader.fs");
	// opengl.shaders.shader = init_shader("./shaders/shader.vs", "./shaders/shader.fs");
	// opengl.textures.texture =  init_textures("./assets/container_diffuse.bmp");
	// init_buffers(&opengl.buffers, mesh);
	init_buffers(&opengl.buffers, mesh);
	// init_camera(&opengl.camera);
	// init_coordinate_systems(&opengl.c_systems);
	// init_tools(&opengl.tools);
	loop(&opengl, mesh);
	// clear_ressources(&opengl.buffers);
}

t_mesh	*cube_mesh(void)
{
	// float vertices[] = {
	// 	1.000000, -1.000000, -1.000000,
	// 	1.000000, -1.000000, 1.000000,
	// 	-1.000000, -1.000000, 1.000000,
	// 	-1.000000, -1.000000, -1.000000,
	// 	1.000000, 1.000000, -0.999999,
	// 	0.999999, 1.000000, 1.000001,
	// 	-1.000000, 1.000000, 1.000000,
	// 	-1.000000, 1.000000, -1.000000
	// };
	float vertices[] = {
		0.500000, -0.500000, -0.500000,
		0.500000, -0.500000, 0.500000,
		-0.500000, -0.500000, 0.500000,
		-0.500000, -0.500000, -0.500000,
		0.500000, 0.500000, -0.5000000,
		0.500000, 0.500000, 0.500000,
		-0.500000, 0.500000, 0.500000,
		-0.500000, 0.500000, -0.500000
	};
	unsigned int indices[] = {
		2, 4, 1,
		8, 6, 5,
		5, 2, 1,
		6, 3, 2,
		3, 8, 4,
		1, 8, 5,
		2, 3, 4,
		8, 7, 6,
		5, 6, 2,
		6, 7, 3,
		3, 7, 8,
		1, 4, 8,
	};
	t_mesh *mesh;
	
	mesh = ft_memalloc(sizeof(t_mesh));
	mesh->vertices = (float *)malloc(sizeof(float) * 24);
	ft_memcpy(mesh->vertices, vertices, sizeof(float) * 24);
	mesh->indices = (unsigned int *)malloc(sizeof(unsigned int) * 36);
	ft_memcpy(mesh->indices, indices, sizeof(unsigned int) * 36);
	mesh->nbr_indices = 36;
	return (mesh);
}

t_mesh	*triangle_mesh(void)
{
	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	t_mesh *mesh;
	
	mesh = ft_memalloc(sizeof(t_mesh));
	mesh->vertices = (float *)malloc(sizeof(float) * 12);
	ft_memcpy(mesh->vertices, vertices, sizeof(float) * 12);
	mesh->indices = (unsigned int *)malloc(sizeof(unsigned int) * 6);
	ft_memcpy(mesh->indices, indices, sizeof(unsigned int) * 6);
	mesh->nbr_indices = 6;
	return (mesh);
}
int		main(int ac, char **args)
{
	t_mesh	*mesh;

	if (ac != 2)
	{
		ft_printf("Usage: ./scop obj_filename\n");
		return (0);
	}
	mesh = load(args[1]);
	if (mesh == NULL)
	{
		// mesh = cube_mesh();
		mesh = triangle_mesh();
		// ft_printf("%d\n", mesh->nbr_indices);
		// ft_printf("Error in file.");
		// return (0);
	}
	run(mesh);
	clear_mesh(mesh);
	return (0);
}
