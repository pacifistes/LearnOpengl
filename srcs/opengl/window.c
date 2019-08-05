/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:40:56 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/04 02:48:19 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static void	init_context(void)
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow	*init_window(void)
{
	GLFWwindow	*window;

	init_context();
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glewExperimental = GL_TRUE;
	glEnable(GL_DEPTH_TEST);
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW\n");
		return (NULL);
	}
	return (window);
}
