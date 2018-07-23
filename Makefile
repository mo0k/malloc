# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 09:22:47 by mo0k              #+#    #+#              #
#    Updated: 2018/07/22 22:56:33 by jmoucade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CFLAGS = -Wall -Werror -Wextra -g
CC = gcc $(CFLAGS)

LIBPRINT_PATH = libftprintf
LIB = $(LIBPRINT_PATH)/libftprintf.a

INC_PATH = includes

INCS = $(INC_PATH)/malloc.h \
		$(INC_PATH)/debug.h 

SRCS_PATH = sources

SRCS = $(SRCS_PATH)/malloc.c 					\
		$(SRCS_PATH)/free.c 					\
		$(SRCS_PATH)/realloc.c 					\
		$(SRCS_PATH)/calloc.c 					\
		$(SRCS_PATH)/show_alloc_mem.c 			\
		$(SRCS_PATH)/block.c 					\
		$(SRCS_PATH)/check_space_and_align.c 	\
		$(SRCS_PATH)/checksum.c 				\
		$(SRCS_PATH)/create_free_blk.c 			\
		$(SRCS_PATH)/memory_manager.c 			\
		$(SRCS_PATH)/manage_free.c 				\
		$(SRCS_PATH)/manage_large.c 			\
		$(SRCS_PATH)/memory_utils.c 			\
		$(SRCS_PATH)/utils.c 					\
		$(SRCS_PATH)/page1.c 					\
		$(SRCS_PATH)/page2.c 					\
		$(SRCS_PATH)/place_free_blk.c 			\
		$(SRCS_PATH)/tiny_small.c				\
		$(SRCS_PATH)/debug.c

OBJS	= $(SRCS:%.c=%.o)
C_LGREEN = "\033[92m"
C_LRED = "\033[91m"
C_RED = "\033[31m"
C_DFL	="\033[0m"

ECHO = echo -n

all: $(NAME)

$(NAME): $(LIB) $(INCS) $(OBJS_PATH) $(OBJS) Makefile
	@$(CC) -shared $(OBJS) -o $(NAME) -L $(LIBPRINT_PATH) -lftprintf
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
