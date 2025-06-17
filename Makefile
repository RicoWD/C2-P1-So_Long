# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/06/17 18:24:34 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#									  CONFIG								   #
#******************************************************************************#

NAME		= 	so_long
CC			=	cc
CFLAGS      =	-Wall -Wextra -Werror -Iinclude -I./minilibx-linux -I./$(LIBFT_DIR)
LDFLAGS		= 	-L./minilibx-linux -lmlx -lX11 -lXext -lm -L./$(LIBFT_DIR) -lft
RM			=	rm -f

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

$(LIBFT_A): $(LIBFT_OBJ)
	@ar rcs $@ $^

clean:
	@$(RM) $(OBJ)
	@$(RM) $(LIBFT_OBJ)
	@echo "CLEAN applied : object files deleted"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_A)
	@echo "FCLEAN applied : all binaries deleted"

re: fclean all

.PHONY: all clean fclean re