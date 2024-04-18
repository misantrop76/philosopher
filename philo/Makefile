# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mminet <mminet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 12:49:58 by mminet            #+#    #+#              #
#    Updated: 2024/04/18 16:00:23 by mminet           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo.c\
		utils.c\
		create_philo.c\

NAME = philo

CC = gcc $(FLAGS)

FLAGS = -Wall -Wextra -Werror -pthread -lpthread

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
