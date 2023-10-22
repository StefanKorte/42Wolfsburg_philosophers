# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 16:51:52 by skorte            #+#    #+#              #
#    Updated: 2022/04/16 09:48:01 by skorte           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=cc
CFLAGS= -Wall -Wextra -Werror -D MICROSECONDS=0
LDFLAGS= -pthread -lpthread

SOURCES	=	philo.c \
			ft_init.c \
			ft_simulation.c \
			ft_actions.c \
			ft_time.c \
			ft_write.c \
			ft_mutex.c \
			ft_free.c \
			ft_conversion_utils.c \
			ft_string_utils.c

OBJECTS=$(SOURCES:.c=.o)

all: $(NAME)

$(OBJECTS):$(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SOURCES)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

no:
	norminette *.c *.h

.PHONY: clean fclean re no
