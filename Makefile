NAME = scop

SRCSPATH = srcs/
INCLUDES = includes/
HEADERS = scop.h \
		scop_math.h
LIBFT = libftprintf
GLEW = /Users/bbrunell/.brew/Cellar/glew/2.1.0/lib
GLFW = /Users/bbrunell/.brew/Cellar/glfw/3.3/lib
GLEWINCL = /Users/bbrunell/.brew/Cellar/glew/2.1.0/include
GLFWINCL = /Users/bbrunell/.brew/Cellar/glfw/3.3/include
LIBFTINCL = libftprintf/printf/includes/

SRCS = main.c \
	tmp.c \
	loader/loader.c \
	loader/register_datas.c \
	loader/datas_tools.c \
	loader/clear_mesh.c \
	opengl/window.c \
	opengl/shader.c \
	opengl/buffers.c \
	opengl/textures.c \
	opengl/camera.c \
	opengl/visual_matrices.c \
	opengl/env.c \
	opengl/set_shaders_variables.c \
	opengl/inputs.c \
	opengl/clear_ressources.c \
	opengl/polygon_mode.c \
	math/math1.c \
	math/math2.c \
	math/math3.c \
	math/math4.c \
	other/read_bmp.c 

SRC = $(addprefix $(SRCSPATH), $(SRCS))

HEADER = $(addprefix $(INCLUDES), $(HEADERS))
WFLAGS = -Wall -Werror -Wextra

CC = gcc -g

OBJ = $(SRC:.c=.o)

all : $(NAME)


libftprintf/libftprintf.a: libftprintf/libft/srcs/ libftprintf/libft/includes/ libftprintf/printf/ libftprintf/libft/includes/ libftprintf/Makefile
	make -C $(LIBFT) all

%.o: %.c $(HEADER)
	$(CC) -c $(WFLAGS) -I $(LIBFTINCL) -I $(INCLUDES) -I $(GLFWINCL) -I $(GLEWINCL) $< -o $@

$(NAME) : libftprintf/libftprintf.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) \
		-L $(LIBFT) -lftprintf \
		-L $(GLFW) -lglfw -framework OpenGL \
		-L $(GLEW) -lglew -framework OpenGL

clean :
	rm -rf $(OBJ)
	make -C $(LIBFT) clean

fclean : clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re : fclean all

.PHONY: all clean fclean re
