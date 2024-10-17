NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS =	srcs/main.c \
		srcs/parsing.c \
		srcs/parsing_utils.c \
		srcs/data_init.c \
		srcs/simulation.c \
		srcs/simulation_utils.c \
		srcs/routines.c \
		srcs/getters_setters.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $^ -o $@

%.o: %.c
	cc $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean all
