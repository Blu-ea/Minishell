# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 09:17:51 by amiguez           #+#    #+#              #
#    Updated: 2022/06/15 06:26:53 by jcollon          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := minishell
# ############################################################################ #
LST_SRCS	:= main.c \
			init.c \
			spit.c
LST_OBJS	:= $(LST_SRCS:.c=.o)
LST_INCS	:= minishell.h
LST_LIBFT	:= libft.a
# ############################################################################ #
DIR_SRCS	:= srcs
DIR_OBJS	:= .objs
DIR_INCS	:= includes
DIR_LIBFT	:= libft
# ############################################################################ #
SRCS		:= $(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS		:= $(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS		:= $(addprefix $(DIR_INCS)/,$(LST_INCS))
LIBFT		:= $(addprefix $(DIR_LIBFT)/,$(LST_LIBFT))
# ############################################################################ #
CC			:= gcc
CFLAGS		:= -Wall -Wextra #-Werror
# ############################################################################ #
NORMITEST	= 
NORMINETTE	= $(shell norminette $(SRCS) | grep -i 'Error')
# ############################################################################ #
all : $(NAME)

$(NAME) : $(OBJS) Makefile $(INCS) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(DIR_INCS) -lreadline -o $@

$(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(DIR_INCS) -lreadline

$(DIR_OBJS) :
	mkdir -p $(DIR_OBJS)

$(LIBFT) :
	git submodule update --remote --rebase $(DIR_LIBFT)
	printf "$(YELLOW)LIBFT IS UP TO DATE!\n$(END)$(RED)"
	make -sC $(DIR_LIBFT)

clean :
	rm -f $(DIR_OBJS)
	make -sC $(DIR_LIBFT) clean

fclean :
	rm -rf $(NAME)
	rm -rf $(DIR_OBJS)
	make -sC $(DIR_LIBFT) fclean

re : fclean all

.PHONY : all clean fclean re $(LIBFT) $(DIR_OBJS)
.SILENT :