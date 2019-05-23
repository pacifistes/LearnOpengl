/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 21:29:29 by bbrunell          #+#    #+#             */
/*   Updated: 2019/05/23 17:48:34 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "ft_printf.h"
# include "scop_math.h"
# include <fcntl.h>
# include <time.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# define SIZE_STOCKAGE 50
# define WIDTH 800.0f
# define HEIGHT 800.0f

typedef struct	s_vertice
{
	double	x;
	double	y;
	double	z;
	double	w;
	void	*next;
}				t_vertice;

typedef struct	s_texture
{
	double	u;
	double	v;
	double	w;
	void	*next;
}				t_texture;

typedef struct	s_normal
{
	double	x;
	double	y;
	double	z;
	void	*next;
}				t_normal;

typedef	struct	s_indice
{
	uint32_t	vertice;
	uint32_t	texture;
	uint32_t	normal;
}				t_indice;

typedef	struct	s_face
{
	t_indice	*indices;
	void		*next;
}				t_face;

typedef	struct	s_group
{
	char	*name;
	t_face	*faces;
	void	*next;
}				t_group;

typedef struct	s_object
{
	char	*name;
	t_group	*groups;
	void	*next;
}				t_object;

typedef struct	s_datas
{
	t_object	*objects;
	t_vertice	*vertices;
	// t_texture	*textures;
	// t_normal	*normals;
}				t_datas;

typedef struct	s_register
{
	char	*format;
	void	(*apply)(char *line, t_datas *datas);
}				t_register;

typedef struct	s_opengl
{
	GLFWwindow	*window;
	GLuint		shader;
	GLuint		vao;
	GLuint		vbo;
	GLuint		ebo;
	GLuint		*vertices;
	GLuint		*indices;
	GLuint		texture;
	GLuint		texture2;
}				t_opengl;

typedef struct s_tmp
{
	float 		angle;
	float		matrice[16];
	float		model[16];
	float		view[16];
	float		projection[16];
	t_vector	camera_pos;
	t_vector	camera_front;
	t_vector	camera_up;
	//Key
	float		delta_time;
	float		last_frame;
	//Mouse
	double		yaw;
	double		pitch;
	double		last_x;
	double		last_y;
	float		fov;
	GLenum 		mode;
}				t_tmp;

t_datas			parse(char *filename);
void			register_vertice(char *str, t_datas *datas);
// void			register_texture(char *str, t_datas *datas);
// void			register_normal(char *str, t_datas *datas);
void			register_face(char *str, t_datas *datas);
void			register_group_name(char *name, t_datas *datas);
void			register_object_name(char *name, t_datas *datas);
void 			insert_group(t_group **groups, char *name);
void			insert_object(t_object **objects, char *name);
void			print_datas(t_datas *datas);
void			clear_datas(t_datas *datas);


/*
**	OPENGL
*/

GLFWwindow		*init_window(void);
GLuint			init_shader(void);
void			init_buffers(t_opengl *opengl);
void			clear_ressources(GLuint *vao, GLuint *vbo, GLuint *ebo);
void			init_textures(t_opengl *opengl);

void 			framebuffer_size_callback(GLFWwindow* window, int width, int height);
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void 			scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void 			mouse_callback(GLFWwindow* window, double xpos, double ypos);
/*
**	OTHER
*/

unsigned char	*read_bmp(char *filename, int *width, int *height);

static const t_register g_registers[] = {
	// {
	// 	"vn",
	// 	&register_normal
	// },
	// {
	// 	"vt",
	// 	&register_texture
	// },
	{
		"o",
		&register_object_name
	},
	{
		"g",
		&register_group_name
	},
	{
		"v",
		&register_vertice
	},
	{
		"f",
		&register_face
	}
};

#endif

/*
**	Vertices
**	 v: X Y Z W with W optional . Default 1.0
**	 Texture
**	 vt: U V W with [V,W] optional between 0.0-1.0. Default  0.0
**	 Vertex
**	 vn: X Y Z
**	 Face
**	 f 1 2 3
**	   f 3/1 4/2 5/3
**	   f 6/4/1 3/5/3 7/6/5
**	   f 7//1 8//2 9//3
**	   f ...
*/
