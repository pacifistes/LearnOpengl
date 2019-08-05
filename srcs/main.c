/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/05 06:16:28 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_render(t_opengl *gl)
{
	update_env(&gl->env);
	update_visual_matrices(&gl->v_matrices, &gl->camera, &gl->env);
	active_textures(&gl->textures);
	set_matrice(gl->shaders.shader, "model", gl->v_matrices.model);
	set_matrice(gl->shaders.shader, "view", gl->v_matrices.view);
	set_matrice(gl->shaders.shader, "projection", gl->v_matrices.projection);
	set_float(gl->shaders.shader, "texture_ratio", gl->env.texture_ratio);
}

void	loop(t_opengl *opengl, t_mesh *mesh)
{
	while (!glfwWindowShouldClose(opengl->window))
	{
		inputs(opengl);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update_render(opengl);
		glUseProgram(opengl->shaders.shader);
		glBindVertexArray(opengl->buffers.vao);
		glDrawElements(GL_TRIANGLES, mesh->nbr_indices, GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(opengl->window);
	}
}

int		run(t_mesh *mesh)
{
	t_opengl opengl;

	if (!mesh)
		return (0);
	opengl.window = init_window();
	init_shaders(&opengl.shaders);
	init_textures(&opengl.textures, &opengl.shaders);
	init_buffers(&opengl.buffers, mesh);
	init_camera(&opengl.camera);
	init_visual_matrices(&opengl.v_matrices);
	init_env(&opengl.env);
	loop(&opengl, mesh);
	clear_ressources(&opengl.buffers);
	return (1);
}

int		main(int ac, char **args)
{
	t_mesh	*mesh;

	mesh = NULL;
	// srand(time(NULL));
	if (ac == 2)
		mesh = load(args[1]);
	else
		printf("Usage: ./scop obj_filename\n");
	if (run(mesh))
		clear_mesh(mesh);
	else
		printf("Error in file.\n");
	return (0);
}
