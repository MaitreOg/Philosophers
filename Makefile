NAME = philo


CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = init.c  main.c utils.c philo.c

OBJECTS = $(SRCS:.c=.o) 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus re