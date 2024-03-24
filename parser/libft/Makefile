# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 19:07:28 by pfontenl          #+#    #+#              #
#    Updated: 2024/01/22 12:45:32 by pfontenl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

PRINTF_MAKE=make --no-print-directory -C ft_printf
PRINTF=ft_printf/libftprintf.a

NAME = libft.a
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_count_char.c ft_find_char.c ft_line_len.c \
ft_tern_char.c ft_tern_int.c ft_tern_ptr.c
OBJS = $(SRCS:.c=.o)

INCLUDE = libft.h Makefile

LIB = ar rcs
RM = rm -f

CC = cc
CCFLAGS = -Wall -Wextra -Werror

COLOR_NONE=\033[0;0m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_YELLOW=\033[1;33m
COLOR_PINK=\033[1;35m
COLOR_CYAN=\033[1;36m

PREFIX=$(COLOR_YELLOW)[LIBFT]$(COLOR_NONE)  

all: $(NAME)

$(NAME): printf $(OBJS) $(INCLUDE)
	@cp $(PRINTF) $(NAME)
	@$(LIB) $(NAME) $(OBJS)
	@echo "$(PREFIX)$(COLOR_GREEN)$(NAME) generado!$(COLOR_NONE)"

%.o: %.c $(INCLUDE)
	@$(CC) $(CCFLAGS) -c -o $@ $<
	@printf "$(PREFIX)$(COLOR_CYAN)$< compilado a $@!$(COLOR_NONE)\n"

printf:
	@echo "$(PREFIX)$(COLOR_CYAN)Compilando ft_printf...$(COLOR_NONE)"
	@$(PRINTF_MAKE)
	@echo "$(PREFIX)$(COLOR_GREEN)ft_printf compilado!$(COLOR_NONE)"

clean:
	@$(PRINTF_MAKE) clean
	@$(RM) $(OBJS)
	@echo "$(PREFIX)$(COLOR_RED)Objectos eliminados!$(COLOR_NONE)"

fclean: clean
	@$(PRINTF_MAKE) fclean
	@$(RM) $(NAME)
	@echo "$(PREFIX)$(COLOR_RED)$(NAME) eliminado!$(COLOR_NONE)"

re: fclean all

.PHONY: all printf clean fclean re