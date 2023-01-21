# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 09:17:51 by amiguez           #+#    #+#              #
#    Updated: 2023/01/21 22:03:02 by jcollon          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := minishell
# ############################################################################ #
DIR_SRCS	:= srcs
DIR_OBJS	:= .objs
DIR_INCS	:= includes
DIR_LIBFT	:= libft
# ############################################################################ #
LST_SRCS	:=	read_line.c\
				init_env.c\
				signal.c\
				debug.c\
				main.c\
				env.c
LST_OBJS	:=	$(LST_SRCS:.c=.o)
LST_INCS	:=	minishell.h
LST_LIBFT	:=	libft.a

BUILTIN		:=	export_update.c\
				print_export.c\
				export_add.c\
				cd_env.c\
				export.c\
				unset.c\
				echo.c\
				exit.c\
				env.c\
				pwd.c\
				cd.c
DIR_BUILTIN	:=	builtins
LST_BUILTIN	:=	$(addprefix $(DIR_BUILTIN)/,$(BUILTIN))
SRC_BUILTIN	:=	$(addprefix $(DIR_SRCS)/,$(LST_BUILTIN))
OBJ_BUILTIN	:=	$(addprefix $(DIR_OBJS)/,$(LST_BUILTIN:.c=.o))

PARSING		:=	dollar_variable.c\
				clean_empty.c\
				split_pipes.c\
				trim_pipe.c\
				get_index.c\
				handlers.c\
				cut_cmd.c\
				utils2.c\
				debug.c\
				utils.c\
				parse.c\
				exit.c
DIR_PARSING	:=	pars
LST_PARSING :=	$(addprefix $(DIR_PARSING)/,$(PARSING))
SRC_PARSING	:=	$(addprefix $(DIR_SRCS)/,$(LST_PARSING))
OBJ_PARSING	:=	$(addprefix $(DIR_OBJS)/,$(LST_PARSING:.c=.o))

EXECUTE		:=	execute_pipe.c\
				fd_lst_utils.c\
				get_redirect.c\
				builtin_exec.c\
				pipe_utils.c\
				open_fork.c\
				execution.c\
				error1.c\
				debug.c\
				pipex.c\
				utils.c\
				pipe.c\
				free.c
DIR_EXECUTE	:=	execute
LST_EXECUTE :=	$(addprefix $(DIR_EXECUTE)/,$(EXECUTE))
SRC_EXECUTE	:=	$(addprefix $(DIR_SRCS)/,$(LST_EXECUTE))
OBJ_EXECUTE	:=	$(addprefix $(DIR_OBJS)/,$(LST_EXECUTE:.c=.o))

# ############################################################################ #
SRCS		:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS)) $(SRC_BUILTIN) $(SRC_PARSING) $(SRC_EXECUTE)
OBJS		:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS)) $(OBJ_BUILTIN) $(OBJ_PARSING) $(OBJ_EXECUTE)
INCS		:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))
LIBFT		:=	$(addprefix $(DIR_LIBFT)/,$(LST_LIBFT))
# DEPH		:=	$(OBJS:=.o=.d)
# -include $(DEPH)
# ############################################################################ #
CC			:=	gcc
SANITYZE	:=	-fsanitize=address
CFLAGS		:=	-Wall -Wextra -g3 #-Werror
# ############################################################################ #
# **************************************************************************** #
ERASE	:=	\033[2K\r
GREY	:=	\033[30m
RED		:=	\033[31m
GREEN	:=	\033[32m
YELLOW	:=	\033[33m
BLUE	:=	\033[34m
PINK	:=	\033[35m
CYAN	:=	\033[36m
WHITE	:=	\033[37m
BOLD	:=	\033[1m
UNDER	:=	\033[4m
SUR		:=	\033[7m
END		:=	\033[0m
# **************************************************************************** #
NORMITEST	=
NORMINETTE	= $(shell norminette $(SRCS) | grep -i 'Error!')
# **************************************************************************** #
# ############################################################################ #
all : $(NAME)

$(NAME) : $(OBJS) Makefile $(INCS) | $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(DIR_INCS) -I$(shell brew --prefix readline)/include -lreadline -L$(shell brew --prefix readline)/lib -o $@ $(SANITYZE)

ifeq ($(NORMINETTE),$(NORMITEST))
	printf "$(GREEN)Everything is ok\n$(END)"
else
	printf "$(RED)$(SUR)NORMINETTE ERROR IN MINISHELL FILES !!\n $(NORMINETTE)$(END)\n"
endif

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(DIR_INCS) -I$(shell brew --prefix readline)/include -MMD $(SANITYZE)

$(DIR_OBJS) :
	mkdir -p $(DIR_OBJS)
	mkdir -p $(DIR_OBJS)/$(DIR_PARSING)
	mkdir -p $(DIR_OBJS)/$(DIR_BUILTIN)
	mkdir -p $(DIR_OBJS)/$(DIR_EXECUTE)

$(LIBFT) :
	# git submodule update --remote --rebase $(DIR_LIBFT)
	# printf "$(YELLOW)LIBFT IS UP TO DATE!\n$(END)$(RED)"
	make -sC $(DIR_LIBFT)

clean :
	rm -rf $(DIR_OBJS)
	make -sC $(DIR_LIBFT) clean

fclean :
	rm -f $(NAME)
	rm -rf $(DIR_OBJS)
	make -sC $(DIR_LIBFT) fclean

re : fclean all

.PHONY : all clean fclean re $(LIBFT)
.SILENT :
