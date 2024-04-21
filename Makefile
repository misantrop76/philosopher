# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mminet <mminet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 12:49:58 by mminet            #+#    #+#              #
#    Updated: 2024/04/21 00:42:56 by mminet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo.c\
		utils.c\
		create_philo.c\

NAME = philo

CC = clang $(FLAGS)

FLAGS = -Wall -Wextra -Werror


OBJ = $(patsubst %.c, obj/%.o, $(SRCS))

HEADER =	philo.h

all: $(NAME)

$(OBJ): ${HEADER}

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

obj/%.o: %.c
	@mkdir -p obj
	$(CC) -c $< -o $@

norme:
	norminette *.c *.h

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all
