# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmouette <jmouette@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 09:48:40 by jmouette          #+#    #+#              #
#    Updated: 2025/01/26 14:32:35 by jmouette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wextra -Werror -Wall

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_number.c ft_chars.c get_next_line.c get_next_line_utils.c \

OBJECTS = $(SOURCES:%.c=%.o)

.SILENT:

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $?

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

SOURCEbONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJECTS = $(SOURCEbONUS:%.c=%.o)

bonus: .bonus

.bonus: $(NAME) $(BONUS_OBJECTS)
	ar -rcs $(NAME) $(BONUS_OBJECTS)
	@touch .bonus

clean:
	rm -f $(OBJECTS)
	rm -f $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f .bonus

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus