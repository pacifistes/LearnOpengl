/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:08:57 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/20 19:48:07 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	(void)scancode;
	(void)mode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// void processInput(GLFWwindow *window)
// {
// 	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 		glfwSetWindowShouldClose(window, true);
// 	float cameraSpeed = 2.5 * deltaTime;
// 	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 		cameraPos += cameraSpeed * cameraFront;
// 	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 		cameraPos -= cameraSpeed * cameraFront;
// 	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
// 	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
// }


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	(void)xpos;
	(void)ypos;
    // if (firstMouse)
    // {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }

    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos;
    // lastX = xpos;
    // lastY = ypos;

    // float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;

    // yaw += xoffset;
    // pitch += yoffset;

    // // make sure that when pitch is out of bounds, screen doesn't get flipped
    // if (pitch > 89.0f)
    //     pitch = 89.0f;
    // if (pitch < -89.0f)
    //     pitch = -89.0f;

    // glm::vec3 front;
    // front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // front.y = sin(glm::radians(pitch));
    // front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	(void)yoffset;
    // if (fov >= 1.0f && fov <= 45.0f)
    //     fov -= yoffset;
    // if (fov <= 1.0f)
    //     fov = 1.0f;
    // if (fov >= 45.0f)
    //     fov = 45.0f;
}