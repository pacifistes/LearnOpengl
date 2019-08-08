/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:29:29 by bbrunell          #+#    #+#             */
/*   Updated: 2019/08/08 12:30:43 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "ft_printf.h"
# include "scop_math.h"
# include "scop_loader.h"
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# define SIZE_STOCKAGE 50
# define WIDTH 800.0f
# define HEIGHT 800.0f
# define KEY_7 0
# define KEY_8 1
# define KEY_9 2
# define KEY_C 3

typedef struct	s_gl_shaders
{
	GLuint		shader;
}				t_gl_shaders;

typedef struct	s_gl_textures
{
	GLuint		texture;
}				t_gl_textures;

typedef struct	s_gl_buffers
{
	unsigned int		vao;
	unsigned int		vbo;
	unsigned int		ebo;
}				t_gl_buffers;

typedef struct	s_gl_camera
{
	t_vector	pos;
	t_vector	front;
	t_vector	up;
}				t_gl_camera;

typedef struct	s_gl_coordinate_system
{
	GLfloat		model[16];
	GLfloat		view[16];
	GLfloat		projection[16];
}				t_gl_coordinate_system;

typedef struct	s_gl_env
{
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			rot_x;
	int			rot_y;
	int			rot_z;
	float		texture_ratio;
	float		delta_time;
	float		last_frame;
	double		yaw;
	double		pitch;
	double		last_x;
	double		last_y;
}				t_gl_env;

typedef struct	s_opengl
{
	GLFWwindow				*window;
	t_gl_shaders			shaders;
	t_gl_buffers			buffers;
	t_gl_textures			textures;
	t_gl_coordinate_system	v_matrices;
	t_gl_camera				camera;
	t_gl_env				env;
}				t_opengl;

/*
**	OPENGL
*/

GLFWwindow		*init_window(void);
void			init_textures(t_gl_textures *textures, t_gl_shaders *shader);
void			init_shaders(t_gl_shaders *shaders);
void			init_buffers(t_gl_buffers *buffers, t_mesh *mesh);
void			init_camera(t_gl_camera *camera);
void			active_textures(t_gl_textures *textures);
void			init_visual_matrices(t_gl_coordinate_system *v_matrices);
void			update_visual_matrices(t_gl_coordinate_system *v_matrices,
t_gl_camera *camera, t_gl_env *env);
void			init_env(t_gl_env *env);
void			update_env(t_gl_env *env);
void			clear_ressources(t_gl_buffers *buffers);
void			mouse_input(GLFWwindow *window, t_gl_camera *camera,
t_gl_env *env);
void			key_input(GLFWwindow *window, t_gl_camera *camera,
float delta_time);
void			set_matrice(GLuint shader, char *str, GLfloat *matrice);
void			set_vector(GLuint shader, char *str, t_vector vector);
void			set_int(GLuint shader, char *str, GLint value);
void			set_float(GLuint shader, char *str, GLfloat value);
void			change_polygon_mode();
void			inputs(t_opengl *opengl);
int				key_up(GLFWwindow *window, int button, int button_index);
int				key_down(GLFWwindow *window, int button);

/*
**	OTHER
*/

unsigned char	*read_bmp(char *filename, int *width, int *height);

#endif
