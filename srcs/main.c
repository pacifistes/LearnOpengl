/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/03 05:05:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	loop(t_opengl *opengl, t_mesh *mesh)
{
	while (!glfwWindowShouldClose(opengl->window))
	{
		key_input(opengl->window, &opengl->camera,
		opengl->tools.delta_time);
		mouse_input(opengl->window, &opengl->camera, &opengl->tools);
		update_tools(&opengl->tools);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		init_coordinate_systems(&opengl->c_systems);
		update_coordinate_systems(&opengl->c_systems, &opengl->camera,
		opengl->tools.angle);
		send_coordinate_systems(&opengl->c_systems, opengl->shaders.shader);
		active_textures(&opengl->textures);
		glUseProgram(opengl->shaders.shader);
		glBindVertexArray(opengl->buffers.vao);
		glDrawElements(GL_TRIANGLES, mesh->nbr_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(opengl->window);
		glfwPollEvents();
	}
}

void	run(t_mesh *mesh)
{
	t_opengl opengl;

	opengl.window = init_window();
	init_shaders(&opengl.shaders);
	init_textures(&opengl.textures, &opengl.shaders);
	init_buffers(&opengl.buffers, mesh);
	init_camera(&opengl.camera);
	init_coordinate_systems(&opengl.c_systems);
	init_tools(&opengl.tools);
	opengl.mode = GL_LINE;
	loop(&opengl, mesh);
	clear_ressources(&opengl.buffers);
}

t_mesh	*cube_mesh(void)
{
	// static float		vertices[] = {
	// 	0.500000, -0.500000, -0.500000, 1.0,
	// 	0.500000, -0.500000, 0.500000, 1.0,
	// 	-0.500000, -0.500000, 0.500000,1.0,
	// 	-0.500000, -0.500000, -0.500000,1.0,
	// 	0.500000, 0.500000, -0.5000000,1.0,
	// 	0.500000, 0.500000, 0.500000,1.0,
	// 	-0.500000, 0.500000, 0.500000,1.0,
	// 	-0.500000, 0.500000, -0.500000, 1.0
	// };
	static float		vertices[] = {
	1.000000, 0.500000, 0.500000, 1.000000,
	1.000000, 0.500000, 1.000000, 1.000000,
	0.500000, 0.500000, 1.000000, 1.000000,
	0.500000, 0.500000, 0.500000, 1.000000,
	1.000000, 1.000000, 0.5, 1.000000,
	0.999999, 1.000000, 1.000001, 1.000000,
	0.500000, 1.000000, 1.000000, 1.000000,
	0.500000, 1.000000, 0.500000, 1.000000
	};
	static unsigned int	indices[] = {
		1, 3, 0, 7, 5, 4, 4, 1, 0, 5, 2, 1,
		2, 7, 3, 0, 7, 4, 1, 2, 3, 7, 6, 5,
		4, 5, 1, 5, 6, 2, 2, 6, 7, 0, 3, 7,
	};
	t_mesh				*mesh;

	mesh = ft_memalloc(sizeof(t_mesh));
	mesh->vertices = (float *)malloc(sizeof(float) * 32);
	ft_memcpy(mesh->vertices, vertices, sizeof(float) * 32);
	mesh->indices = (unsigned int *)malloc(sizeof(unsigned int) * 36);
	ft_memcpy(mesh->indices, indices, sizeof(unsigned int) * 36);
	mesh->nbr_indices = 36;
	mesh->nbr_vertices = 32;
	return (mesh);
}

t_mesh	*triangle_mesh(void)
{
	static float		vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	static unsigned int	indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	t_mesh				*mesh;

	mesh = ft_memalloc(sizeof(t_mesh));
	mesh->vertices = (float *)malloc(sizeof(float) * 12);
	ft_memcpy(mesh->vertices, vertices, sizeof(float) * 12);
	mesh->indices = (unsigned int *)malloc(sizeof(unsigned int) * 6);
	ft_memcpy(mesh->indices, indices, sizeof(unsigned int) * 6);
	mesh->nbr_indices = 6;
	mesh->nbr_vertices = 12;
	return (mesh);
}

/*
**	mesh = cube_mesh();
**	mesh = triangle_mesh();
*/

int		main(int ac, char **args)
{
	t_mesh	*mesh;
	unsigned int i;

	if (ac != 2)
	{
		ft_printf("Usage: ./scop obj_filename\n");
		return (0);
	}
	mesh = load(args[1]);
	// mesh = NULL;
	(void)args;
	if (mesh == NULL)
	{
		mesh = cube_mesh();
		ft_printf("Error in file.");
		// return (0);
	}
	i = 0;
	while (i < mesh->nbr_vertices)
	{
		printf("v %f %f %f %f\n", mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2], mesh->vertices[i + 3]);
		i += 4;
	}
	i = 0;
	while (i < mesh->nbr_indices)
	{
		printf("f %u %u %u\n", mesh->indices[i], mesh->indices[i + 1], mesh->indices[i + 2]);
		i += 3;
	}
	run(mesh);
	clear_mesh(mesh);
	return (0);
}
