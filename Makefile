# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 12:16:53 by mhrima            #+#    #+#              #
#    Updated: 2022/11/03 10:25:35 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -rf
SRC = ft_printf.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	$(RM) *.o

bonus:

fclean: clean
	$(RM) $(NAME)

re: fclean all