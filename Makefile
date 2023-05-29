CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Ilibft/includes
NAME = pipex
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIBRARY = libft/libft.a

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -g3
endif

all: $(NAME)

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY):
	$(MAKE) -j8 -C libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
