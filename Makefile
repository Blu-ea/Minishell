# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 09:17:51 by amiguez           #+#    #+#              #
#    Updated: 2022/07/03 11:08:27 by amiguez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
# ############################################################################ #
DIR_SRCS	:= srcs
DIR_OBJS	:= .objs
DIR_INCS	:= includes
DIR_LIBFT	:= libft
# ############################################################################ #
LST_SRCS	:=	main.c\
				init.c\
				pars.c\
				split.c\
				free_data.c
LST_OBJS	:= $(LST_SRCS:.c=.o)
LST_INCS	:= minishell.h
LST_LIBFT	:= libft.a

BUILTIN		:=	cd.c\
				env.c\
				echo.c\
				exit.c\
				cd.c\
				export.c\
				unset.c
DIR_BUILTIN	:=	builtins
LST_BUILTIN	:=	$(addprefix $(DIR_BUILTIN)/,$(BUILTIN))
SRC_BUILTIN	:=	$(addprefix $(DIR_SRCS)/,$(LST_BUILTIN))
OBJ_BUILTIN	:=	$(addprefix $(DIR_OBJS)/,$(LST_BUILTIN:.c=.o))
# ############################################################################ #
SRCS		:= $(addprefix $(DIR_SRCS)/,$(LST_SRCS)) $(SRC_BUILTIN)
OBJS		:= $(addprefix $(DIR_OBJS)/,$(LST_OBJS)) $(OBJ_BUILTIN)
INCS		:= $(addprefix $(DIR_INCS)/,$(LST_INCS))
LIBFT		:= $(addprefix $(DIR_LIBFT)/,$(LST_LIBFT))
# ############################################################################ #
CC			:= gcc
CFLAGS		:= -Wall -Wextra #-Werror
SANITYZE	:= -fsanitize=address -g
# ############################################################################ #
# **************************************************************************** #
ERASE	=	\033[2K\r
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PINK	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
END		=	\033[0m
# **************************************************************************** #
NORMITEST = 
NORMINETTE = $(shell norminette $(SRCS) | grep -i 'Error')
# **************************************************************************** #
# ############################################################################ #
all : $(NAME)

$(NAME) : $(OBJS) Makefile $(INCS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(DIR_INCS) -lreadline -o $@ 

ifeq ($(NORMINETTE),$(NORMITEST))
	printf "$(GREEN)Everything is ok\n$(END)"
else
	printf "$(RED)$(SUR)NORMINETTE ERROR IN MINISHELL FILES !!\n $(NORMINETTE)$(END)"
endif

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(DIR_INCS)

$(DIR_OBJS) :
	mkdir -p $(DIR_OBJS)
	mkdir -p $(DIR_OBJS)/$(DIR_BUILTIN)

$(LIBFT) :
	git submodule update --remote --rebase $(DIR_LIBFT)
	printf "$(YELLOW)LIBFT IS UP TO DATE!\n$(END)$(RED)"
	make -C $(DIR_LIBFT)

clean :
	rm -f $(DIR_OBJS)
	make -C $(DIR_LIBFT) clean

fclean :
	rm -rf $(NAME)
	rm -rf $(DIR_OBJS)
	make -C $(DIR_LIBFT) fclean

re : fclean all

.PHONY : all clean fclean re libft
# .SILENT :