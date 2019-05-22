NAME = scop

SRCSPATH = srcs/
INCLUDES = includes/
HEADERS = scop.h
LIBFT = libftprintf
GLEW = /Users/bbrunell/.brew/Cellar/glew/2.1.0/lib
GLFW = /Users/bbrunell/.brew/Cellar/glfw/3.3/lib
GLEWINCL = /Users/bbrunell/.brew/Cellar/glew/2.1.0/include
GLFWINCL = /Users/bbrunell/.brew/Cellar/glfw/3.3/include
LIBFTINCL = libftprintf/printf/includes/

SRCS = main.c \
	parser/parser.c \
	parser/register_faces.c \
	parser/register_names.c \
	parser/datas_tools.c \
	opengl/init_window.c \
	opengl/init_shader.c \
	opengl/init_buffers.c \
	opengl/init_textures.c \
	opengl/callbacks.c \
	opengl/clear_ressources.c \
	math/math1.c \
	math/math2.c \
	math/math3.c \
	other/read_bmp.c 

SRC = $(addprefix $(SRCSPATH), $(SRCS))

HEADER = $(addprefix $(INCLUDES), $(HEADERS))
WFLAGS = -Wall -Werror -Wextra

CC = gcc -g

OBJ = $(SRC:.c=.o)

all : $(NAME)


libftprintf/libftprintf.a: libftprintf/libft/srcs/ libftprintf/libft/includes/ libftprintf/printf/ libftprintf/libft/includes/ libftprintf/Makefile
	make -C $(LIBFT) all

%.o: %.c
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
