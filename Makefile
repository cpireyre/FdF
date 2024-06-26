# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 09:17:29 by copireyr          #+#    #+#              #
#    Updated: 2024/06/26 13:16:02 by copireyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:
UNAME_S := $(shell uname -s)

bin 		:= fdf
src_dir 	:= ./src
obj_dir 	:= ./obj
inc_dir		:= ./include
sources 	:= main.c build_map.c transform.c  \
			   assign_colors.c rasterize.c clip.c interpolate_color.c
objects 	:= $(sources:%.c=$(obj_dir)/%.o)
libft_dir	:= ./libft
libmlx_dir	:= ./MLX42
libft		:= $(libft_dir)/libft.a
libmlx 		:= $(libmlx_dir)/build/libmlx42.a

CC			:= clang
debug		:= -fsanitize=undefined -fsanitize=address -g3
# optimization := -O2
CFLAGS		:= -Wconversion $(debug) $(optimization)
CFLAGS		+= -Wall -Wextra -Werror -MMD -MP -pedantic
LDFLAGS		:= -L$(libft_dir) -lft -L$(libmlx_dir)/build -lmlx42 $(debug)
ifeq ($(UNAME_S), Darwin)
LDFLAGS		+= -framework Cocoa -framework OpenGL -framework IOKit
endif
LDFLAGS += -Iinclude -ldl -lglfw -pthread -lm
CPPFLAGS	:= -I$(inc_dir) -I$(libft_dir)/include -I$(libmlx_dir)/include
cmakeflags	:= -DCMAKE_C_FLAGS="-Wno-int-to-void-pointer-cast"

$(obj_dir)/%.o: $(src_dir)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(libft):
	CFLAGS="$(CFLAGS)" $(MAKE) -j4 -C $(libft_dir)

$(libmlx):
	cmake $(cmakeflags) $(libmlx_dir) -B $(libmlx_dir)/build > /dev/null
	$(MAKE) -C $(libmlx_dir)/build > /dev/null

ifeq ($(UNAME_S), Darwin)
glfw_path += $(shell brew --prefix glfw)/lib
endif
$(bin): $(libmlx) $(libft) $(objects)
	LIBRARY_PATH=$(glfw_path) $(CC) $(objects) $(LDFLAGS) -o $@

.PHONY: all
all: $(bin) | norm #tags

#tags: $(addprefix $(src_dir)/, $(sources))
	#ctags --recurse

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
	$(RM) -r $(libmlx_dir)/build
	@$(MAKE) -C $(libft_dir) fclean

.PHONY: re
re: fclean all

.PHONY: run
run: $(bin)
	./$(bin) ./test_maps/42.fdf
.PHONY: r
r: run

.PHONY: j
j: $(bin)
	./$(bin) ./test_maps/julia.fdf

.PHONY: m
m: $(bin)
	./$(bin) ./test_maps/mars.fdf

.PHONY: l
l: $(bin)
	./$(bin) ./test_maps/line.fdf

.PHONY: norm
ifeq ($(shell command -v norminette),)
norm:
	@echo "norminette not installed, skipping lint check."
else
norm:
	@norminette $(src_dir) $(libft_dir) $(inc_dir) | grep -v "OK" || true
endif

-include $(objects:.o=.d)
