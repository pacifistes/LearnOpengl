/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:43:32 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/22 20:29:51 by bbrunell         ###   ########.fr       */
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
void	loop(t_opengl *opengl)
{
	float angle = 0.0;
	float matrice[16];
	t_vector	cameraPos;
	t_vector	cameraFront;
	t_vector	cameraUp;

	init_matrice(matrice, 1.0f);
	cameraPos = new_vector(0.0f, 0.0f, 3.0f);
	cameraFront = new_vector(0.0f, 0.0f, -1.0f);
	cameraUp = new_vector(0.0f, 1.0f, 0.0f);
	int firstMouse = 1;//bool
	float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch =  0.0f;
	float lastX =  800.0f / 2.0;
	float lastY =  600.0 / 2.0;
	float fov   =  45.0f;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	(void)firstMouse;
	(void)yaw;
	(void)pitch;
	(void)lastX;
	(void)lastY;
	(void)lastFrame;
	(void)deltaTime;
	(void)fov;
	// t_vector cubePositions[] = {
	//     new_vector( 0.0f,  0.0f,  0.0f),
	//     new_vector( 2.0f,  5.0f, -15.0f),
	//     new_vector(-1.5f, -2.2f, -2.5f),
	//     new_vector(-3.8f, -2.0f, -12.3f),
	//     new_vector( 2.4f, -0.4f, -3.5f),
	//     new_vector(-1.7f,  3.0f, -7.5f),
	//     new_vector( 1.3f, -2.0f, -2.5f),
	//     new_vector( 1.5f,  2.0f, -2.5f),
	//     new_vector( 1.5f,  0.2f, -1.5f),
	//     new_vector(-1.3f,  1.0f, -1.5f)
	// };


	glUseProgram(opengl->shader);
	glUniform1i(glGetUniformLocation(opengl->shader, "texture1"), 0);
	glUniform1i(glGetUniformLocation(opengl->shader, "texture2"), 1);
	glUniformMatrix4fv(glGetUniformLocation(opengl->shader, "transform"), 1, GL_FALSE, matrice);
	while (!glfwWindowShouldClose(opengl->window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, opengl->texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, opengl->texture2);
		glUseProgram(opengl->shader);

		// create transformations
		// float projection[16];
		// float view[16];
		// float model[16];
		// init_matrice(model, 1.0f);
		// init_matrice(projection, 1.0f);
		// init_matrice(view, 1.0f);
		// rotate_with_axis(model,  20.0f, new_vector(1.0f, 0.0f, 0.0f));
		// // translate(view, new_vector(0.0f, 0.0f, -3.0f));
		// perspective(projection, 45.0f, (float)WIDTH / (float)HEIGHT);
		// // retrieve the matrix uniform locations
		// unsigned int modelLoc = glGetUniformLocation(opengl->shader, "model");
		// unsigned int viewLoc  = glGetUniformLocation(opengl->shader, "view");
		// // pass them to the shaders (3 different ways)
		// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
		// glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
		// // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		// set_matrice(opengl->shader, "projection", projection);

		// // render container
		// glBindVertexArray(opengl->vao);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		float model[16];
		float view[16];
		float projection[16];
		init_matrice(model, 1.0f);
		init_matrice(view, 1.0f);
		init_matrice(projection, 1.0f);

		// rotate_with_axis(model, angle, new_vector(0.5f, 1.0f, 1.0f));
		// perspective(projection, 45.0f, (float)WIDTH / (float)HEIGHT);
		
		// print_matrice(model);
		// exit(1);
		// translate(view, new_vector(0.0f, 0.0f, -0.3f));


        float radius = 10.0f;
        float camX   = sin(glfwGetTime()) * radius;
        float camZ   = cos(glfwGetTime()) * radius;
        look_at(view, new_vector(camX, 0.0f, camZ), new_vector(0.0f, 0.0f, 0.0f), new_vector(0.0f, 1.0f, 0.0f));

		// print_matrice(view);
		set_matrice(opengl->shader, "model", model);
		set_matrice(opengl->shader, "view", view);
		set_matrice(opengl->shader, "projection", projection);

		// glRotatef(10.0,0.0,0.0,1.0);            // 3
		// glRotatef(10.0,1.0,0.0,0.0);            // 3
		// glRotatef(10.0,0.0,1.0,0.0);  

		glBindVertexArray(opengl->vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);//TO DELETE
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // NUMBERS OF INDIC

		glBindVertexArray(0);
		glfwSwapBuffers(opengl->window);
		angle += 0.1;
		// usleep(1000);
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



// // create transformations
// glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
// glm::mat4 projection    = glm::mat4(1.0f);
// projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
// view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
// // pass transformation matrices to the shader
// ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
// ourShader.setMat4("view", view);

// // render boxes
// glBindVertexArray(VAO);
// for(unsigned int i = 0; i < 10; i++)
// {
//     // calculate the model matrix for each object and pass it to shader before drawing
//     glm::mat4 model;
//     model = glm::translate(model, cubePositions[i]);
//     float angle = 20.0f * i; 
//     if(i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
//         angle = glfwGetTime() * 25.0f;
//     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//     ourShader.setMat4("model", model);
	
//     glDrawArrays(GL_TRIANGLES, 0, 36);           
// }