# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mo0k <mo0k@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 09:22:47 by mo0k              #+#    #+#              #
#    Updated: 2018/01/12 17:49:44 by mo0k             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CFLAGS = -Wall -Werror -Wextra
CC = gcc $(CFLAGS)

LIBPRINT_PATH = libftprintf
LIB = $(LIBPRINT_PATH)/libftprintf.a

INC_PATH = includes

INCS = $(INC_PATH)/malloc.h

SRCS_PATH = sources

SRCS = $(SRCS_PATH)/malloc.c 			\
		$(SRCS_PATH)/free.c 			\
		$(SRCS_PATH)/realloc.c 			\
		$(SRCS_PATH)/calloc.c 			\
		$(SRCS_PATH)/others.c 			\
		$(SRCS_PATH)/block.c 			\
		$(SRCS_PATH)/map.c 				\
		$(SRCS_PATH)/checksum.c 		\
		$(SRCS_PATH)/memory_manager.c 	\
		$(SRCS_PATH)/show_alloc_mem.c

OBJS	= $(SRCS:%.c=%.o)
C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(LIB) $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	@$(CC) $(CFLAGS) -shared $(OBJS) -o $(NAME) -L $(LIBPRINT_PATH) -lftprintf
	@/bin/rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo $(C_LGREEN)"$(NAME) compiled"$(C_DFL)

$(LIB):
	@make -C $(LIBPRINT_PATH)

%.o: %.c
	@$(CC) -I $(INC_PATH) -I $(LIBPRINT_PATH)/includes -c -o $@ $<
	@echo "Linking file" $@

clean:
	@make clean -C $(LIBPRINT_PATH)
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBPRINT_PATH)
	@if [ -e $(NAME) ]; \
	then echo $(C_RED)"Delete $(NAME)."$(C_DFL); \
	fi;
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: objects OBJS clean fclean