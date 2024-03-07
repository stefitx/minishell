# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/03 16:38:51 by atudor            #+#    #+#              #
#    Updated: 2024/03/03 16:38:55 by atudor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I./inc -I./readline
RM		=	rm -fr

NAME	=	minishell
COMP	=	./inc/libft/libft.a

INPUT_FILES	= minishell.c
BUILTIN_FILES = cd.c
# EXPANSOR_FILES	=
# PARSER_FILES	=
# LEXER_FILES	=
EXEC_FILES	= exec.c
# HEREDOC_FILES	=
# BONUS_FILES	=

HEADER	= ./inc/minishell.h
LIBFT_ROOT	:=	./inc/libft/
RDLINE_ROOT	:=	./inc/readline/
DIR_OBJ		:=	temp/
INC_ROOT	:=	inc/m
SRCS_DIR	=	srcs/

BUILTIN_DIR	=	built-ins/
EXEC_DIR	=	exec/
EXPAN_DIR	=	expan/
HERE_DIR	=	heredoc/
INPUT_DIR	=	input/
LEXER_DIR	=	lex/
PARSER_DIR	=	pars/

INPUT_SRC	=	$(addprefix $(SRCS_DIR),$(addprefix $(INPUT_DIR),$(INPUT_FILES)))
BUILTIN_SRC	=	$(addprefix $(SRCS_DIR),$(addprefix $(BUILTIN_DIR),$(BUILTIN_FILES)))
EXEC_SRC	=	$(addprefix $(SRCS_DIR),$(addprefix $(EXEC_DIR),$(EXEC_FILES)))

INPUT_OBJ	=	$(addprefix $(DIR_OBJ),$(INPUT_SRC:.c=.o))
BUILTIN_OBJ	=	$(addprefix $(DIR_OBJ),$(BUILTIN_SRC:.c=.o))
EXEC_OBJ	=	$(addprefix $(DIR_OBJ),$(EXEC_SRC:.c=.o))

LIB_A		:=	./inc/readline/libreadline.a \
				./inc/libft/libft.a ./inc/readline/libhistory.a

LIB_ADD_DIR	:=	-L$(RDLINE_ROOT) -L$(LIBFT_ROOT)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

HEADERS		:=	$(INC_ROOT)
HEADERS		+=	$(addsuffix $(INC_ROOT),$(LIBFT_ROOT))

#RULES

all : temp libraries $(NAME)

libraries:
	@$(MAKE) -C $(LIBFT_ROOT) --no-print-directory
	@$(MAKE) rdline --no-print-directory

$(NAME): $(INPUT_OBJ) $(BUILTIN_OBJ) $(EXEC_OBJ)
	@$(CC) $(CFLAGS) $^ $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $@

rdline: temp $(RDLINE_ROOT)libreadline.a
# 	@cd $(RDLINE_ROOT) && ./configure
# 	@make -C $(RDLINE_ROOT)

$(DIR_OBJ)%.o: %.c Makefile $(LIB_A) $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DREADLINE_LIBRARY=1 $(INCLUDE) -c $< -o $@

temp	:
	@mkdir -p $(DIR_OBJ)

clean	:
	@$(MAKE) -C $(LIBFT_ROOT) clean --no-print-directory
	@$(RM) $(DIR_OBJ)


fclean	: clean
	@$(MAKE) -C $(LIBFT_ROOT) clean --no-print-directory
	@$(RM) $(NAME)
# 	@$(MAKE) -C $(RDLINE_ROOT) clean --no-print-directory

re		: fclean all

.PHONY : all clean fclean re libraries rdline

.SILENT: