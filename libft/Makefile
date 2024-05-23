# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 15:14:47 by copireyr          #+#    #+#              #
#    Updated: 2024/05/23 15:16:18 by copireyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
CPPFLAGS := -I./include

libft := libft.a
src := ./mem/ft_bzero.c   ./mem/ft_memchr.c  ./mem/ft_memcmp.c \
       ./mem/ft_memcpy.c  ./mem/ft_memmove.c ./mem/ft_memset.c  \
       ./str/ft_strnstr.c ./str/ft_strrchr.c ./str/ft_strdup.c   \
       ./str/ft_strlcpy.c ./str/ft_strlen.c  ./str/ft_strncmp.c   \
       ./str/ft_strndup.c ./str/ft_strjoin.c ./str/ft_strlcat.c    \
       ./str/ft_split.c   ./str/ft_strchr.c  ./str/ft_strtrim.c     \
       ./str/ft_substr.c  ./ctype/ft_atoi.c  ./ctype/ft_isdigit.c

gnl_src := ./gnl/get_next_line.c ./gnl/get_next_line_utils.c 

ft_printf_src := ./ft_printf/src/emit.c       \
		 ./ft_printf/src/ft_printf.c   \
		 ./ft_printf/src/ft_ulltoa.c    \
		 ./ft_printf/src/ptrformat.c     \
		 ./ft_printf/src/parse_bonus.c    \
		 ./ft_printf/src/intformat_bonus.c \
		 ./ft_printf/src/strformat_bonus.c  \
		 ./ft_printf/src/charformat_bonus.c  \
		 ./ft_printf/src/uintformat_bonus.c

obj_dir := ./obj

$(obj_dir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

gnl_object := $(obj_dir)/ft_gnl.o
$(gnl_object): $(gnl_src:./gnl/%.c=$(obj_dir)/gnl/%.o)
	ld -r $^ -o $@

ft_printf_object := $(obj_dir)/ft_printf.o
$(ft_printf_object): $(ft_printf_src:./ft_printf/%.c=$(obj_dir)/ft_printf/%.o)
	ld -r $^ -o $@

obj := $(src:%.c=$(obj_dir)/%.o) $(gnl_object) $(ft_printf_object)

$(libft): $(obj)
	ar rcs $@ $?

.PHONY: all
all: $(libft)

.PHONY: clean
clean:
	@$(RM) $(obj) $(obj:.o=.d)
	@$(RM) -r $(obj_dir) 2> /dev/null || true

.PHONY: fclean
fclean: clean
	$(RM) $(libft)

.PHONY: re
re: fclean all

-include $(client_objects:.o=.d) $(server_objects:.o=.d)
