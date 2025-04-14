# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: assabich <assabich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 15:12:44 by assabich          #+#    #+#              #
#    Updated: 2025/03/27 12:25:32 by assabich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft 
FT_PRINTF_FLAGS = -L$(FT_PRINTF_DIR) -lftprintf
INCLUDE = -I includes -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) 

# Source Files and Object Files
SRC = srcs/main.c srcs/map.c srcs/parsing.c srcs/move.c srcs/accessible.c srcs/render.c srcs/utils.c
OBJ = $(SRC:.c=.o)

# Targets
all: $(NAME)  # Default target is to build the executable

# Build the executable
$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)  # Compile MiniLibX
	$(MAKE) -C $(LIBFT_DIR) # Compile Libft
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) $(LIBFT_FLAGS) $(FT_PRINTF_FLAGS)  # Link everything together

# Clean object files
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean  # Clean Libft
	$(MAKE) -C $(MLX_DIR) clean    # Clean MiniLibX
	$(MAKE) -C $(FT_PRINTF_DIR) clean
# Full clean (including executable)
fclean: clean
	rm -f $(NAME)  # Remove the executable
	$(MAKE) -C $(FT_PRINTF_DIR) fclean  # Clean Libft completely
	$(MAKE) -C $(LIBFT_DIR) fclean
	# No fclean in MiniLibX, so we just run clean instead
	$(MAKE) -C $(MLX_DIR) clean 

re: fclean all

