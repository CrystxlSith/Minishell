# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 14:48:39 by crystal           #+#    #+#              #
#    Updated: 2024/07/22 08:04:42 by jopfeiff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
       ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
       ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
       ft_strchr.c ft_strncmp.c ft_memcmp.c ft_memchr.c\
       ft_strnstr.c ft_atoi.c ft_strrchr.c ft_substr.c \
       ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
       ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
       ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_printf.c ft_printf_utils.c ft_print_str.c \
       ft_print_char.c ft_print_unsigned.c ft_print_hex.c \
       ft_print_ptr.c ft_print_nb.c get_next_line.c \
       get_next_line_utils.c ft_isspace.c
SRCSB = ft_lstnew.c ft_lstadd_front.c \
	ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c ft_lstmap.c 
OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCSB:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.SILENT:

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

bonus: ${NAME} ${OBJSB}
	${LIBC} ${NAME} ${OBJSB}

clean:
	${RM} ${OBJS} ${OBJSB}

fclean: clean
	${RM} ${NAME} ${bonus} 

re: fclean all

.PHONY : all bonus clean fclean re