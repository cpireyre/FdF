NAME := fdf

LIBFT_DIR := ./libft/
LIBFT := ./libft/libft.a

LIBMLX	:= ./lib/MLX42
HEADERS	:= -I$(LIBFT_DIR) -I./include -I$(LIBMLX)/include \
	   -I./gnl
LIBS	:= #$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

CC := cc
CFLAGS := -Wall -Wextra -Werror
CFLAGS += $(HEADERS) $(LIBS)
CFLAGS += -g -fsanitize=address

SRC_DIR := ./src/
SRC_FILES := main.c readlines.c read_elevation.c vec.c \
	     get_next_line.c get_next_line_utils.c
SRC := $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR := ./obj/
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): libft libmlx $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: libmlx
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.PHONY: libft
libft:
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: run
run: $(NAME)
	./$(NAME) test_maps/10-2.fdf
