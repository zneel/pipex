NAME = pipex
BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD
INCLUDES = -Iinclude -Ilibft/includes

SRC =	src/main.c \
		src/path.c \
		src/pipe.c \
		src/utils.c \
		src/commands.c \
		src/execute.c \
		src/pipes.c \
		src/usage.c

SRC_BONUS = src_bonus/main_bonus.c \
			src/path.c \
			src/pipe.c \
			src/commands.c \
			src/execute.c \
			src/pipes.c \
			src_bonus/utils_bonus.c \
			src_bonus/here_doc_bonus.c \
			src_bonus/usage_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
MMD = $(SRC:.c=.d)

LIBRARY = libft/libft.a

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=address
endif

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY):
	$(MAKE) -j8 -C  libft

$(BONUS): $(OBJ_BONUS) $(LIBRARY)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BONUS) $(OBJ_BONUS) $(LIBRARY)

clean:
	rm -f $(OBJ) $(OBJ_BONUS) $(MMD)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
