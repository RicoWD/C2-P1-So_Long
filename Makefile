# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/07/02 13:55:03 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

#******************************************************************************#
#							   MINILIBX OS CHOICE							   #
#******************************************************************************#

UNAME_S			:= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	MLX_DIR		:= minilibx-macos
	MLX_LIB		:= $(MLX_DIR)/libmlx.a
	MLX_INC		:= -I$(MLX_DIR)
	MLX_LDFLAGS	:= $(MLX_LIB) -framework OpenGL -framework AppKit
else
	MLX_DIR		:= minilibx-linux
	MLX_LIB		:= $(MLX_DIR)/libmlx_Linux.a
	MLX_INC		:= -I$(MLX_DIR)
	MLX_LDFLAGS	:= -L$(MLX_DIR) -lmlx -lX11 -lXext
endif

#******************************************************************************#
#									  CONFIG								   #
#******************************************************************************#

NAME		= 	so_long
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iinclude -g -I./include $(MLX_INC) -I$(LIBFT_DIR) -DTILE=$(TILE)
LDFLAGS		=	$(MLX_LDFLAGS) -L$(LIBFT_DIR) -lft -lm
RM			=	/bin/rm -f
TILE		?=	32
LIBFT_DIR	=	libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a
LIBFT_SRC	=	$(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJ	=	$(LIBFT_SRC:.c=.o)

SRC_DIR     =	src
SRC         =	main.c $(wildcard $(SRC_DIR)/*.c)
OBJ         =	$(SRC:.c=.o) $(LIBFT_OBJ)

#******************************************************************************#
#									   RULES								   #
#******************************************************************************#

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "✅  $(NAME) built"

$(LIBFT_A): $(LIBFT_OBJ)
	@ar rcs $@ $^

clean:
	@$(RM) $(OBJ)
	@$(RM) $(LIBFT_OBJ)
	@echo "✅  Objects files deleted"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_A)
	@echo "✅  Binaries deleted"

re: fclean all

test:
	valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(NAME) maps/map0.ber

dev: 
	@make re 1>/dev/null
	@make clean 1>/dev/null
	@echo "✅  Library created and objects deleted"

.PHONY: all clean fclean re dev