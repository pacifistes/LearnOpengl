/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/15 18:18:02 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	loop(t_opengl *opengl)
{
	glUseProgram(opengl->shader);
	glUniform1i(glGetUniformLocation(opengl->shader, "texture1"), 0);
	glUniform1i(glGetUniformLocation(opengl->shader, "texture2"), 1);
	float theta = 0.0f;
	while (!glfwWindowShouldClose(opengl->window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, opengl->texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, opengl->texture2);
		glUseProgram(opengl->shader);
		glBindVertexArray(opengl->vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // NUMBERS OF INDIC
		glBindVertexArray(0);
		glfwSwapBuffers(opengl->window);
		theta += 1.0f;
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
