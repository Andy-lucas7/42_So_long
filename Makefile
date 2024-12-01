NAME	:= so_long
CC		:= cc
CFLAGS	:= -g3 -Wextra -Wall -Werror
FLAGSOMLX := -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft
FLAGSMLX = -ldl -lglfw -pthread -lm
HEADERS	:= -I ./include -I $(LIBMLX)/include -I./src/so_long.h 
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
SRCS	:= ./src/main.c ./src/ft_map.c ./src/ft_display.c ./src/ft_read_map.c \
			./src/ft_moves.c ./src/ft_init.c ./src/ft_flood_fill.c 

OBJS	:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make all bonus new_fun -C $(LIBFT) $(FLAGS) --no-print-directory

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME) $(FLAGSMLX)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx