# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 09:17:29 by copireyr          #+#    #+#              #
#    Updated: 2024/05/23 09:48:31 by copireyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

libmlx_dir	:= ./MLX42
libft_dir	:= ./libft
libft		:= $(libft_dir)/libft.a
libmlx 		:= $(libmlx_dir)/build/libmlx42.a

CC			:= clang
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP
LDFLAGS		:= -L$(libft_dir) -lft -L$(libmlx_dir)/build -lmlx42
CPPFLAGS	:= -I./include -I$(libft_dir)/include -I$(libmlx_dir)/include

binary 	:= FdF
src_dir := ./src
obj_dir := ./obj
sources := main.c
objects := $(sources:%.c=$(obj_dir)/%.o)

$(obj_dir)/%.o: $(src_dir)/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(libft):
	$(MAKE) -j$(shell nproc) -C $(libft_dir) > /dev/null

$(libmlx):
	cmake $(libmlx_dir) -B $(libmlx_dir)/build > /dev/null
	$(MAKE) -j$(shell nproc) -C $(libmlx_dir)/build > /dev/null

$(binary): $(libmlx) $(libft) $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $@

.PHONY: all
all: $(binary)

.PHONY: bonus
bonus: $(binary)

.PHONY: clean
clean:
	$(RM) $(objects) $(objects:.o=.d)
	@rmdir $(obj_dir) 2> /dev/null || true
	@$(RM) -r $(libmlx_dir)/build > /dev/null
	@$(MAKE) -C $(libft_dir) clean > /dev/null

.PHONY: fclean
fclean: clean
	$(RM) $(binary)
	@$(MAKE) -C $(libft_dir) fclean

.PHONY: re
re: fclean all

.PHONY: debug
target debug: CFLAGS  += -g -fsanitize=address -fsanitize=undefined
target debug: LDFLAGS += -g -fsanitize=address -fsanitize=undefined
debug: re

.PHONY: norm
norm:
	@norminette ./src ./include | grep --invert-match "OK" || true

-include $(objects:.o=.d)
