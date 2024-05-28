# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 16:38:51 by atudor            #+#    #+#              #
#    Updated: 2024/04/26 13:11:59 by pfontenl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_NONE=\033[0;0m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_YELLOW=\033[1;33m
COLOR_PINK=\033[1;35m
COLOR_CYAN=\033[1;36m

PREFIX=$(COLOR_YELLOW)[MINISHELL]$(COLOR_NONE)  

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address
INCLUDE	=	-I./inc -I./readline 
RM		=	rm -fr

NAME	=	minishell
COMP	=	./inc/libft/libft.a

ENV_FILES =	env_add_var.c \
			env_clear_all.c \
			env_clear_var.c \
			env_get_var.c \
			env_init.c \
			env_len.c \
			env_set_var.c \
			env_to_arr.c \
			env_unset_var.c \
			env_valid_name_substr.c \
			env_valid_name.c
INPUT_FILES	= minishell.c
BUILTIN_FILES = cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				export_utils.c \
				pwd.c \
				unset.c
# EXPANSOR_FILES	=
PARSER_FILES =	command_builder.c \
				ft_split_set.c \
				parser_utils.c \
				pipe_token_utils.c \
				redir_token_utils.c \
				refined_token_utils.c \
				refiner_utils.c \
				refiner.c \
				single_command_utils.c \
				ft_strappend.c \
				str_node_utils.c \
				text_token_utils.c \
				token_utils.c \
				tokenizer.c # ft_split_set.c and ft_strappend.c should be moved to libft
# LEXER_FILES	=
EXEC_FILES	=	exec.c \
				init_xcmd.c \
				init_utils.c \
				redirections.c \
				exec_utils.c \
				pipexstuff.c \
# HEREDOC_FILES	=
# BONUS_FILES	=

HEADER		=	./inc/minishell.h
LIBFT_ROOT	:=	./inc/libft/
RDLINE_ROOT	:=	./inc/readline/
DIR_OBJ		:=	temp/
INC_ROOT	:=	inc/m
SRCS_DIR	=	srcs/

ENV_DIR		= env/
BUILTIN_DIR	= built-ins/
EXEC_DIR	= exec/
# EXPAN_DIR	= expan/
# HERE_DIR	= heredoc/
INPUT_DIR	= input/
# LEXER_DIR	= lex/
PARSER_DIR	= parser/


ENV_SRC		= $(addprefix $(SRCS_DIR),$(addprefix $(ENV_DIR),$(ENV_FILES)))
INPUT_SRC	= $(addprefix $(SRCS_DIR),$(addprefix $(INPUT_DIR),$(INPUT_FILES)))
BUILTIN_SRC	= $(addprefix $(SRCS_DIR),$(addprefix $(BUILTIN_DIR),$(BUILTIN_FILES)))
EXEC_SRC	= $(addprefix $(SRCS_DIR),$(addprefix $(EXEC_DIR),$(EXEC_FILES)))
PARSER_SRC	= $(addprefix $(SRCS_DIR),$(addprefix $(PARSER_DIR),$(PARSER_FILES)))

ENV_OBJ		= $(addprefix $(DIR_OBJ),$(ENV_SRC:.c=.o))
INPUT_OBJ	= $(addprefix $(DIR_OBJ),$(INPUT_SRC:.c=.o))
BUILTIN_OBJ	= $(addprefix $(DIR_OBJ),$(BUILTIN_SRC:.c=.o))
EXEC_OBJ	= $(addprefix $(DIR_OBJ),$(EXEC_SRC:.c=.o))
PARSER_OBJ	= $(addprefix $(DIR_OBJ),$(PARSER_SRC:.c=.o))

LIB_A		:=	./inc/readline/libreadline.a \
 				./inc/libft/libft.a ./inc/readline/libhistory.a

LIB_ADD_DIR	:=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(LIBFT_ROOT))
HEADERS		+=	$(addsuffix $(INC_ROOT),env.h)
HEADERS		+=	$(addsuffix $(INC_ROOT),parser.h)

#Gross but gets the job done
# ifeq ($(HOME), /Users/pfontenl)
# 	RDLINE_ROOT	=	./inc/readline/
# 	LIB_A =			./inc/readline/libreadline.a \
#  					./inc/libft/libft.a ./inc/readline/libhistory.a
# 	LIB_ADD_DIR	=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT)
# endif

#RULES
all: temp libraries $(NAME)

temp:
	@mkdir -p $(DIR_OBJ)

libraries: libft rdline

$(NAME): $(ENV_OBJ) $(INPUT_OBJ) $(BUILTIN_OBJ) $(EXEC_OBJ) $(PARSER_OBJ)
	@$(CC) $(CFLAGS) $^ $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@
	@echo "$(PREFIX)$(COLOR_GREEN)Minishell built successfully!$(COLOR_NONE)"

libft:
	@$(MAKE) -C $(LIBFT_ROOT) --no-print-directory

$(RDLINE_ROOT)libreadline.a: rdline

rdline:	$(RDLINE_ROOT)libreadline.a
	# cd $(RDLINE_ROOT) && ./configure && make --no-print-directory

$(DIR_OBJ)%.o: %.c Makefile $(LIB_A) $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@
	@printf "$(PREFIX)$(COLOR_CYAN)Compiled $< to $@!$(COLOR_NONE)\n"

clean:
	@$(MAKE) -C $(LIBFT_ROOT) clean --no-print-directory
	@$(MAKE) -C $(RDLINE_ROOT) clean --no-print-directory
	@$(RM) $(DIR_OBJ)
	@echo "$(PREFIX)$(COLOR_RED)Objects deleted successfully!$(COLOR_NONE)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(PREFIX)$(COLOR_RED)Minishell deleted successfully!$(COLOR_NONE)"

re: fclean all

.PHONY: all clean fclean re libraries libft rdline

.SILENT: