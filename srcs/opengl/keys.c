/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 00:12:42 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/07 00:18:13 by bbrunell         ###   ########.fr       */
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
	static int	keys[] = {
		GLFW_RELEASE,
		GLFW_RELEASE,
		GLFW_RELEASE,
		GLFW_RELEASE
	};
	int			key_press;

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
