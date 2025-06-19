# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 15:11:19 by jmouette          #+#    #+#              #
#    Updated: 2025/02/26 16:44:05 by jmouette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D

CC				= cc

CFLAGS			= -Wextra -Wall -Werror #-g -Wunreachable-code -Ofast -fsanitize=address
MLX_FLAGS		= -lglfw -ldl -pthread -lm

LIBFT			= ./libft/libft.a
LIBFT_DIR		= ./libft

MLX42_DIR		= MLX42
MLX42_BUILD_DIR	= MLX42/build
MLX42			= $(MLX42_BUILD_DIR)/libmlx42.a

HEADER			= ./include/cub3D.h

SRCS			= main.c init_game.c validate/validate_cub.c validate/validate_textures.c\
				validate/validate_rgb.c validate/utils_validate.c validate/copy_map.c\
				validate/validate_map.c validate/validate_walls.c\
				read_map.c free.c images.c game_events.c move_player.c rotate_player.c\
				player.c ray_casting.c render_game.c free_pixel.c get_wall_pixels.c\

SOURCES_DIR		= src
OBJS_DIR		= obj

FILES			= $(addprefix $(SOURCES_DIR)/, $(SRCS))
OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

.SILENT:

$(OBJS_DIR)/%.o: $(SOURCES_DIR)/%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_BUILD_DIR)/libmlx42.a:
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	mkdir -p $(MLX42_BUILD_DIR)
	cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4

$(NAME): $(LIBFT) $(MLX42) $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(MLX_FLAGS) -o $(NAME)
	echo "cub3D compiled"

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(MLX42_BUILD_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean
	echo "cub3D clean"

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	echo "cub3D fclean"

re: fclean all

rebonus: fclean

.PHONY: all clean fclean re libft mlx42
