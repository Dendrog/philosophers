NAME =          philo

SRCS =  main.c\
		ft_atoi.c\

HEADR = philo.h

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

OBJS = $(SRCS:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJS) $(HEADR)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
