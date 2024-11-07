NAME	= miniRT
CFLAGS	= -Wextra -Wall -Werror -O3

# libft
LIBFT	= -L./libft -lft

# mlx
MLX_URL = https://github.com/42Paris/minilibx-linux.git
MLX_DIR = ./minilibx-linux
MLX = -L ./$(MLX_DIR) -lmlx -lXext -lX11 -lm -lpthread

#header
HEADERS = -I./include -I./libft -I ./$(MLX_DIR)

# src files
SRCS_DIR = src
SRCS_SUBDIR = pre_handler tools entities renderer vector fclass debug
VPATH = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SRCS_SUBDIR))
SRCS =	main.c \
		error.c magic_s.c check.c \
		validate.c init.c file.c map.c \
		light.c shape.c ambient.c camera.c sphere.c viewport.c \
		color.c draw.c \
		vector_calculate.c vector_tools.c \
		fclass.c \
		debug_shape.c 

OBJS_DIR = objs
OBJS = $(SRCS:.c=.o)
TARGETS = $(addprefix $(OBJS_DIR)/, $(OBJS))


all: clone $(NAME)

clone:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_URL); \
	fi

$(OBJS_DIR)/%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(TARGETS)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C ./libft
	@cc $(CFLAGS) $(TARGETS) $(LIBFT) $(MLX) -o $(NAME) -lreadline

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
