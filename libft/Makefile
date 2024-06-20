# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 15:14:47 by copireyr          #+#    #+#              #
#    Updated: 2024/06/20 14:12:31 by copireyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

CC		 := clang
CFLAGS	 += -Wall -Wextra -Werror -Wsign-conversion
CPPFLAGS := -I./include

libft := libft.a

ft_printf_src := ./ft_printf/src/emit.c       \
				 ./ft_printf/src/ft_printf.c   \
				 ./ft_printf/src/ft_ulltoa.c    \
				 ./ft_printf/src/ptrformat.c     \
				 ./ft_printf/src/parse_bonus.c    \
				 ./ft_printf/src/intformat_bonus.c \
				 ./ft_printf/src/strformat_bonus.c  \
				 ./ft_printf/src/charformat_bonus.c  \
				 ./ft_printf/src/uintformat_bonus.c

src := ./io/ft_gnl.c      ./ctype/ft_atoi.c    ./str/ft_split.c \
	   ./mem/ft_bzero.c   ./mem/ft_memchr.c    ./mem/ft_memcmp.c \
	   ./mem/ft_memcpy.c  ./mem/ft_memset.c    ./str/ft_strdup.c  \
	   ./str/ft_strlen.c  ./str/ft_strchr.c    ./str/ft_substr.c   \
	   ./str/ft_strcat.c  ./mem/ft_memmove.c   ./str/ft_strnstr.c   \
	   ./str/ft_strrchr.c ./str/ft_strlcpy.c   ./str/ft_strncmp.c    \
	   ./str/ft_strndup.c ./str/ft_strjoin.c   ./str/ft_strlcat.c     \
	   ./str/ft_strtrim.c ./ctype/ft_isdigit.c ./mem/ft_memdel.c       \
	   ./io/ft_error.c	  ./ctype/ft_isspace.c ./arena/arena.c 			\
	   ./math/ft_abs.c 	  ./math/fixed_point.c

obj_dir := ./obj
$(obj_dir)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

ft_printf_obj := $(obj_dir)/ft_printf.o
ft_printf_objs:= $(ft_printf_src:./ft_printf/%.c=$(obj_dir)/ft_printf/%.o)
$(ft_printf_obj): $(ft_printf_objs)
	ld -r $^ -o $@

obj := $(src:%.c=$(obj_dir)/%.o) $(ft_printf_obj)
$(libft): $(obj)
	ar rcs $@ $?

.PHONY: all
all: $(libft)

.PHONY: clean
clean:
	@$(RM) $(obj) $(obj:.o=.d)
	$(RM) -r $(obj_dir)

.PHONY: fclean
fclean: clean
	$(RM) $(libft)

.PHONY: re
re: fclean all

-include $(obj:.o=.d) $(ft_printf_objs:.o=.d)
