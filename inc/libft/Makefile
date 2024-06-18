# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 18:39:11 by atudor            #+#    #+#              #
#    Updated: 2023/09/29 23:21:35 by atudor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_bzero.c ft_memcpy.c ft_memset.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c \
		ft_malloc_err.c ft_calloc_err.c ft_strdup_err.c ft_substr_err.c \
		ft_strjoin_err.c ft_strjoin_err.c ft_strtrim_err.c ft_itoa_err.c ft_split_err.c

SRCSBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			ft_lstmap.c	
 			
OBJS = ${SRCS:.c=.o}
OBJSBONUS = ${SRCSBONUS:.c=.o}
NAME = libft.a
HEADER = libft.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
 
%.o:%.c 	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: 		${NAME}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

bonus:		${OBJS} ${OBJSBONUS}
			ar rcs ${NAME} ${OBJS} ${OBJSBONUS}
			@touch $@

clean: 		
			${RM} ${OBJS} ${OBJSBONUS}

fclean: 	clean
			${RM} ${NAME}
			${RM} bonus

re:			fclean all

.PHONY: all clean fclean re
