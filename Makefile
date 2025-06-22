NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -g3

SRCS = src/L1.c src/L2.c src/L3_A.c src/L3_B.c\
	src/L4.c src/LCE.c src/LGU.c src/main.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	make clean
	clear
	./philo 5 800 200 200

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
