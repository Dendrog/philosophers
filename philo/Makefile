NAME =          philo

SRCS =  main.c\
		ft_atoi.c\
		arg.c\
		eat.c\
		fork.c\
		ft_sleep.c\
		logic.c\
		sleep.c\
		think.c\
		utils.c

HEADR = philo.h

CC = cc
CFLAGS = -Wall -Wextra -Werror

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
