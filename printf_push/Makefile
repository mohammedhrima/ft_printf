# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/06 10:43:33 by mhrima            #+#    #+#              #
#    Updated: 2022/11/06 13:53:22 by mhrima           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -rf
SRC1 = ft_printf.c
OBJ1 = ft_printf.o
SRC2 = lib/convert.c lib/len.c lib/others.c lib/put.c lib/printf_utils_handle_flag.c lib/printf_utils_handle_output_1.c lib/printf_utils_handle_output_2.c
OBJ2 = convert.o len.o others.o put.o printf_utils_handle_flag.o printf_utils_handle_output_1.o printf_utils_handle_output_2.o

all: $(NAME)
	
$(OBJ2): $(SRC2)
	$(CC) $(FLAGS) -c $(SRC2)

$(OBJ1): $(SRC1)
	$(CC) $(FLAGS) -c $<

$(NAME): $(OBJ1) $(OBJ2)
	$(AR) $(NAME) $(OBJ1) $(OBJ2)


clean:
	$(RM) *.o

bonus:

fclean: clean
	$(RM) $(NAME)

re: fclean all