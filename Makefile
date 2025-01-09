NAME	= miniRT
CFLAGS	= -Wextra -Wall -Werror -O3

# libft
LIBFT	= -L./libft -lft

# mlx
MLX_URL = https://github.com/42Paris/minilibx-linux.git
MLX_DIR = ./minilibx-linux
MLX = -L ./$(MLX_DIR) -lmlx -lXext -lX11 -lm -lpthread

#header
HEADERS = -I ./mandatory/include -I ./libft -I ./$(MLX_DIR) -I ./bonus/include

# src files & targets
SRCS_DIR = mandatory/src
SRCS_SUBDIR = entities fclass hook init menu parser renderer tools vector bvh debug
VPATH = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SRCS_SUBDIR))
SRCS =	main.c \
		ambient.c camera.c cylinder.c cylinder_inter.c light.c plane.c shape.c sphere.c \
		fclass.c \
		hook.c preset.c update_click.c update_hold.c camera_preset.c\
		init.c validate.c backup.c \
		menu.c menu_tool.c camera_menu.c light_menu.c shape_menu.c view_menu.c \
		parse_args.c parse_tool.c \
		color.c illumination.c intersection.c ray.c reflect.c render.c \
		equation.c error.c magic_s.c tool.c \
		vector_op_basic.c vector_op_plus.c vector_tools.c vector_rotate.c \
		bvh.c bvh_tool.c bvh_intersection.c aabb.c \
		debug_shape.c 

OBJS_DIR = objs
OBJS = $(SRCS:.c=.o)
TARGETS = $(addprefix $(OBJS_DIR)/, $(OBJS))

# bonus files & targets
BONUS_SRCS_DIR = bonus/src
BONUS_SUBDIR = entities fclass hook init intersection menu parser renderer tools vector bvh debug color
BONUS_VPATH = $(BONUS_SRCS_DIR) $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SUBDIR))
BONUS_SRCS =	main_bonus.c \
				ambient_bonus.c camera_bonus.c cone_bonus.c cylinder_bonus.c light_bonus.c plane_bonus.c shape_bonus.c  sphere_bonus.c normal_bonus.c\
				fclass_bonus.c \
				hook_bonus.c preset_bonus.c update_click_bonus.c update_hold_bonus.c camera_preset_bonus.c \
				init_bonus.c validate_bonus.c backup_bonus.c \
				inter_cone_bonus.c inter_cylinder_bonus.c inter_plane_bonus.c inter_sphere_bonus.c \
				menu_bonus.c menu_tool_bonus.c camera_menu_bonus.c light_menu_bonus.c shape_menu_bonus.c view_menu_bonus.c \
				parse_args_bonus.c parse_tool_bonus.c \
				illumination_bonus.c intersection_bonus.c ray_bonus.c reflect_bonus.c render_bonus.c \
				equation_bonus.c error_bonus.c magic_s_bonus.c tool_bonus.c \
				vector_op_basic_bonus.c vector_op_plus_bonus.c vector_tools_bonus.c vector_rotate_bonus.c \
				bvh_bonus.c bvh_tool_bonus.c bvh_intersection_bonus.c aabb_bonus.c \
				debug_shape_bonus.c \
				uv_bonus.c \
				color_bonus.c color_utils_bonus.c texture_bonus.c
				
BONUS_OBJS_DIR = objs_bonus
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_TARGETS = $(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_OBJS))

# vpath choose
ifeq ($(MAKECMDGOALS), bonus)
    VPATH = $(BONUS_VPATH)
endif

# make rules
all: clone $(NAME)

bonus: clone $(BONUS_OBJS_DIR) $(BONUS_TARGETS)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C ./libft
	@cc $(CFLAGS) $(BONUS_TARGETS) $(LIBFT) $(MLX) -o $(NAME) -lreadline

clone:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_URL); \
	fi

# mandatory
$(OBJS_DIR)/%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(TARGETS)
	@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C ./libft
	@cc $(CFLAGS) $(TARGETS) $(LIBFT) $(MLX) -o $(NAME) -lreadline

# bonus
$(BONUS_OBJS_DIR)/%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(BONUS_OBJS_DIR):
	mkdir -p $(BONUS_OBJS_DIR)

# clean
clean:
	@rm -rf $(OBJS_DIR) $(BONUS_OBJS_DIR)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX_DIR)
	@$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
