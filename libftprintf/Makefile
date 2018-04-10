# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/31 09:06:42 by mo0ky             #+#    #+#              #
#    Updated: 2018/04/02 22:36:36 by mo0k             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

ifdef FLAGS
	ifeq ($(FLAGS), no)
		CFLAGS=
	endif
	ifeq ($(FLAGS), debug)
		CFLAGS= -Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
	CFLAGS = -Wall -Wextra -Werror
endif

CC = gcc $(CFLAGS) -g

INC_PATH = includes

INCS = $(INC_PATH)/ft_printf.h	\
		$(INC_PATH)/fmt.h		\
		$(INC_PATH)/fmt_types.h \
		$(INC_PATH)/colors.h \
		$(INC_PATH)/libft.h

SRCS_PATH = sources
SRCS_PRINTF =	$(SRCS_PATH)/ft_printf.c		\
				$(SRCS_PATH)/analyze_format.c 	\
				$(SRCS_PATH)/get_format.c 	\
				$(SRCS_PATH)/format_string.c 	\
				$(SRCS_PATH)/do_filler.c 		\
				$(SRCS_PATH)/color.c 		\
				$(SRCS_PATH)/convch/parser.c			\
				$(SRCS_PATH)/convch/init_var/fmt.c		\
				$(SRCS_PATH)/convch/init_var/signed.c	\
				$(SRCS_PATH)/convch/init_var/unsigned.c	\
				$(SRCS_PATH)/convch/convert/tools/utils_unsigned.c	\
				$(SRCS_PATH)/convch/convert/tools/do_preci_and_fill.c	\
				$(SRCS_PATH)/convch/convert/tools/do_sign.c	\
				$(SRCS_PATH)/convch/convert/tools/do_space.c	\
				$(SRCS_PATH)/convch/convert/tools/fix_counter.c	\
				$(SRCS_PATH)/convch/convert/tools/more_speed.c	\
				$(SRCS_PATH)/convch/convert/tools/ret_error.c	\
				$(SRCS_PATH)/convch/convert/char.c		\
				$(SRCS_PATH)/convch/convert/string.c	\
				$(SRCS_PATH)/convch/convert/uint.c		\
				$(SRCS_PATH)/convch/convert/int.c		\
				$(SRCS_PATH)/convch/convert/hexa.c		\
				$(SRCS_PATH)/convch/convert/octal.c		\
				$(SRCS_PATH)/convch/convert/binary.c		\
				$(SRCS_PATH)/convch/convert/no_convert.c

LIBFT_PATH = $(SRCS_PATH)/libft
SRCS_LIBFT = $(LIBFT_PATH)/ft_strlen.c 	\
				$(LIBFT_PATH)/ft_atoi.c \
				$(LIBFT_PATH)/ft_isdigit.c \
				$(LIBFT_PATH)/ft_memmove.c \
				$(LIBFT_PATH)/ft_memcpy.c \
				$(LIBFT_PATH)/ft_memrcpy.c \
				$(LIBFT_PATH)/ft_memcmp.c \
				$(LIBFT_PATH)/ft_memset.c \
				$(LIBFT_PATH)/ft_strchr.c \
				$(LIBFT_PATH)/ft_strcmp.c \
				$(LIBFT_PATH)/ft_strncpy.c \
				$(LIBFT_PATH)/ft_strtoupper.c \
				$(LIBFT_PATH)/ft_toupper.c \
				$(LIBFT_PATH)/buffer/available_space.c \
				$(LIBFT_PATH)/buffer/fill_buffer.c \
				$(LIBFT_PATH)/buffer/filln_buffer.c \
				$(LIBFT_PATH)/buffer/init.c

SRCS = $(SRCS_LIBFT) $(SRCS_PRINTF)

OBJS	= $(SRCS:%.c=%.o)
C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	@ar rcs $(NAME) $(OBJS)
	@libtool -static -o $(NAME) $(OBJS) $(LIB)
	@echo $(C_LGREEN)"$(NAME) compiled"$(C_DFL)

%.o: %.c
	@$(CC) -I $(INC_PATH) -I $(LIB_PATH)/$(INC_PATH) -c -o $@ $<
	@echo "Linking file" $@

clean: 
	@/bin/rm -f $(OBJS)

fclean: clean
	@if [ -e $(NAME) ]; \
	then echo $(C_RED)"Delete $(NAME)."$(C_DFL); \
	fi;
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: objects OBJS clean fclean