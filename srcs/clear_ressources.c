/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ressources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 16:57:39 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/12 18:27:21 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	clear_ressources(GLuint *vao, GLuint *vbo, GLuint *ebo)
{
	glDeleteVertexArrays(1, vao);
	glDeleteBuffers(1, vbo);
	glDeleteBuffers(1, ebo);
	glfwTerminate();
}