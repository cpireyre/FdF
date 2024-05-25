# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 09:17:29 by copireyr          #+#    #+#              #
#    Updated: 2024/05/25 16:23:29 by copireyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

bin 		:= FdF
src_dir 	:= ./src
obj_dir 	:= ./obj
inc_dir		:= ./include
sources 	:= main.c render.c
objects 	:= $(sources:%.c=$(obj_dir)/%.o)
libft_dir	:= ./libft
libmlx_dir	:= ./MLX42
libft		:= $(libft_dir)/libft.a
libmlx 		:= $(libmlx_dir)/build/libmlx42.a

CC			:= clang
CFLAGS		:= -Wconversion -std=c89
CFLAGS		+= -Wall -Wextra -Werror -MMD -MP -pedantic
LDFLAGS		:= -L$(libft_dir) -lft -L$(libmlx_dir)/build -lmlx42
LDFLAGS		+= -framework Cocoa -framework OpenGL -framework IOKit
LDFLAGS		+= -ldl -lglfw -pthread -lm
CPPFLAGS	:= -I$(inc_dir) -I$(libft_dir)/include -I$(libmlx_dir)/include


$(obj_dir)/%.o: $(src_dir)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(libft):
	$(MAKE) -j4 -C $(libft_dir) > /dev/null

$(libmlx):
	cmake $(libmlx_dir) -B $(libmlx_dir)/build > /dev/null
	$(MAKE) -j4 -C $(libmlx_dir)/build > /dev/null

glfw_path := "$(shell brew --cellar)/glfw/3.4/lib"
$(bin): $(libmlx) $(libft) $(objects)
	LIBRARY_PATH=$(glfw_path) $(CC) $(objects) $(LDFLAGS) -o $@

.PHONY: all
all: $(bin) | norm

.PHONY: bonus
bonus: $(bin)

.PHONY: clean
clean:
	$(RM) $(objects) $(objects:.o=.d)
	@rmdir $(obj_dir) 2> /dev/null || true
	@$(RM) -r $(libmlx_dir)/build > /dev/null
	@$(MAKE) -C $(libft_dir) clean > /dev/null

.PHONY: fclean
fclean: clean
	$(RM) $(bin)
	@$(MAKE) -C $(libft_dir) fclean

.PHONY: re
re: fclean all

debug_flags := -g3 -fsanitize=address -fsanitize=undefined
.PHONY: debug
target debug: CFLAGS  += $(debug_flags)
target debug: LDFLAGS += $(debug_flags)
debug: re

.PHONY: run
run: $(bin)
	./$(bin)

.PHONY: norm
ifeq ($(shell command -v norminette),)
norm:
	@echo "norminette not installed, skipping lint check."
else
norm:
	@norminette $(src_dir) $(libft_dir) $(inc_dir) | grep -v "OK" || true
endif

-include $(objects:.o=.d)
