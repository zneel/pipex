NAME = pipex
BONUS = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD
INCLUDES = -Iinclude -Ilibft/includes

SRC =	src/main.c \
		src/path.c \
		src/pipe.c \
		src/utils.c

OBJ = $(SRC:.c=.o)
LIBRARY = libft/libft.a

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY):
	$(MAKE) -j8 -C libft

bonus: $(BONUS)

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
