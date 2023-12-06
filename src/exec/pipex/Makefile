# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raphael <raphael@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 13:41:30 by rtissera          #+#    #+#              #
#    Updated: 2023/06/28 17:15:28 by raphael          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

SRC_DIR			:= src
OBJ_DIR			:= obj
LIBFT_DIR		:= libft
SRCS			:=	\
	main.c			\
	utils/utils.c
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT			:= $(LIBFT_DIR)/libft.a

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I include

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#

RM			:= rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBFT)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

$(LIBFT):
	make -C $(LIBFT_DIR)
	$(info CREATED $(LIBFT))

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

norminette:
	norminette include
	norminette src

re: fclean all

run: re
	-./$(NAME)

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#
.PHONY: clean fclean re run
.SILENT:
