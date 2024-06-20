# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 09:17:29 by copireyr          #+#    #+#              #
#    Updated: 2024/06/20 14:21:10 by copireyr         ###   ########.fr        #
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
sources 	:= main.c render.c build_map.c project.c move.c draw.c bresenham.c \
			   interpolate_color.c 
objects 	:= $(sources:%.c=$(obj_dir)/%.o)
libft_dir	:= ./libft
libmlx_dir	:= ./MLX42
libft		:= $(libft_dir)/libft.a
libmlx 		:= $(libmlx_dir)/build/libmlx42.a

CC			:= clang
CFLAGS		:= -Wconversion
CFLAGS		+= -Wall -Wextra -Werror -MMD -MP -pedantic
LDFLAGS		:= -L$(libft_dir) -lft -L$(libmlx_dir)/build -lmlx42
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
	CFLAGS="$(CFLAGS)" $(MAKE) -C $(libft_dir)

$(libmlx):
	cmake $(cmakeflags) $(libmlx_dir) -B $(libmlx_dir)/build > /dev/null
	$(MAKE) -C $(libmlx_dir)/build > /dev/null

ifeq ($(UNAME_S), Darwin)
	glfw_path := $(shell brew --prefix glfw)/lib
endif
$(bin): $(libmlx) $(libft) $(objects)
	LIBRARY_PATH=$(glfw_path) $(CC) $(objects) $(LDFLAGS) -o $@

.PHONY: all
all: $(bin) | norm tags

tags: $(addprefix $(src_dir)/, $(sources))
	ctags --recurse

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

debug_flags := -g3 -fsanitize=address -fsanitize=undefined
.PHONY: debug
target debug: CFLAGS  += $(debug_flags)
target debug: LDFLAGS += $(debug_flags)
debug: re

.PHONY: run
run: $(bin)
	./$(bin) ./test_maps/42.fdf
.PHONY: r
r: run

leaks_flags := -g3
.PHONY: leaks
target leaks: CFLAGS  += $(leaks_flags)
target leaks: LDFLAGS += $(leaks_flags)
leaks: fclean all
	leaks -atExit -quiet -- ./$(bin) test_maps/basictest.fdf

test_flags := -g3
.PHONY: test
target test: CFLAGS  += $(test_flags)
target test: LDFLAGS += $(test_flags)
test: fclean all
	leaks -atExit -quiet -- ./$(bin) test_maps/2x1.fdf
	# leaks -atExit -quiet -- ./$(bin) test_maps/space_after.fdf
	leaks -atExit -quiet -- ./$(bin) test_maps/missing_last.fdf
	leaks -atExit -quiet -- ./$(bin) test_maps/wrong_cols.fdf
	leaks -atExit -quiet -- ./$(bin) nonexistentmap
	leaks -atExit -quiet -- ./$(bin) test_maps/empty_map
	# leaks -atExit -quiet -- ./$(bin) test_maps/basictest.fdf
	# leaks -atExit -quiet -- ./$(bin) test_maps/just_one.fdf

.PHONY: norm
ifeq ($(shell command -v norminette),)
norm:
	@echo "norminette not installed, skipping lint check."
else
norm:
	@norminette $(src_dir) $(libft_dir) $(inc_dir) | grep -v "OK" || true
endif

-include $(objects:.o=.d)
