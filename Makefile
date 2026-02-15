CC = cc
CFLAGS = -Wall -Wextra -Werror
HDRS = philo.h

NAME = philo

SRCS = ft_init.c ft_parsing.c ft_threads.c ft_threads_utils.c ft_utils.c main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: