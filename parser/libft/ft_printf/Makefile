# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/30 13:00:56 by pfontenl          #+#    #+#              #
#    Updated: 2024/01/22 12:45:32 by pfontenl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

NAME=libftprintf.a
SRCS=	ft_printf.c \
		printf_backend.c \
		write_chars.c \
		write_nums.c
OBJS=$(SRCS:.c=.o)

INCLUDE=Makefile ft_printf.h

LIB=ar rcs
RM=rm -f

CC=cc
CCFLAGS=-Wall -Wextra -Werror

COLOR_NONE=\033[0;0m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_YELLOW=\033[1;33m
COLOR_PINK=\033[1;35m
COLOR_CYAN=\033[1;36m

PREFIX=$(COLOR_YELLOW)[PRINTF]$(COLOR_NONE)  

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@$(LIB) $(NAME) $(OBJS)
	@echo "$(PREFIX)$(COLOR_GREEN)$(NAME) generado!$(COLOR_NONE)"

%.o: %.c $(INCLUDE)
	@$(CC) $(CCFLAGS) -c -o $@ $<
	@printf "$(PREFIX)$(COLOR_CYAN)$< compilado a $@!$(COLOR_NONE)\n"

clean:
	@$(RM) $(OBJS)
	@echo "$(PREFIX)$(COLOR_RED)Objetos eliminados!$(COLOR_NONE)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(PREFIX)$(COLOR_RED)$(NAME) eliminado!$(COLOR_NONE)"

re: fclean all

.PHONY: all clean fclean re