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

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP
LDFLAGS		:= -L$(libft_dir) -lft -L$(libmlx_dir)/build -lmlx42
CPPFLAGS	:= -I./include/ -I$(libft_dir)/include -I$(libmlx_dir)/include

name 	:= FdF
src_dir := ./src
obj_dir := ./obj
sources := main.c
objects := $(sources:%.c=$(obj_dir)/%.o)

$(libft):
	$(MAKE) -j -C $(libft_dir) > /dev/null

$(libmlx):
	cmake $(libmlx_dir) -B $(libmlx_dir)/build > /dev/null
	$(MAKE) -j -C $(libmlx_dir)/build > /dev/null

$(obj_dir)/%.o: $(src_dir)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
	@$(RM) -r $(libmlx_dir)/build > /dev/null
	@$(MAKE) -C $(libft_dir) clean > /dev/null

.PHONY: fclean
fclean: clean
	$(RM) $(name)
	@$(MAKE) -C $(libft_dir) fclean

.PHONY: re
re: fclean all

.PHONY: debug
debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined
debug: re

.PHONY: norm
norm:
	@norminette ./src ./include | grep --invert-match "OK" || true

-include $(objects:.o=.d)
