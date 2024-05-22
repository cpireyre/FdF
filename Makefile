.DEFAULT_GOAL := all
.SUFFIXES:

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
CPPFLAGS := -I./include/ -I./libft/include
libft_dir := ./libft/
libft := $(libft_dir)libft.a
libmlx_dir := ./MLX42
libmlx := ./MLX42/build/libmlx42.a
LDFLAGS := -L$(libft_dir) -lft

name := FdF
src_dir := ./src
obj_dir := ./obj
sources := main.c
objects := $(sources:%.c=$(obj_dir)/%.o)

$(libft):
	$(MAKE) -C $(libft_dir) > /dev/null

$(libmlx):
	@cmake $(libmlx_dir) -B $(libmlx_dir)/build > /dev/null
	@make -C $(libmlx_dir)/build -j4 > /dev/null

$(obj_dir)/%.o: $(src_dir)/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(name): $(libmlx) $(libft) $(objects)
	$(CC) $(CFLAGS) $(LDFLAGS) $(objects) -o $@

.PHONY: all
all: $(name)

.PHONY: bonus
bonus: $(name)

.PHONY: clean
clean:
	$(RM) $(objects) $(objects:.o=.d)
	@rmdir $(obj_dir) 2> /dev/null || true
	@$(MAKE) -C $(libft_dir) clean > /dev/null
	@$(RM) -r $(libmlx_dir)/build > /dev/null

.PHONY: fclean
fclean: clean
	$(RM) $(name)
	@$(MAKE) -C $(libft_dir) fclean

.PHONY: re
re: fclean all

.PHONY: debug
debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined
debug: all

-include $(objects:.o=.d)
