# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/26 14:08:00 by jsingh            #+#    #+#              #
#    Updated: 2026/07/26 14:18:18 by jsingh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = ft_printf.c ft_printf_utils.c ft_printf_converters.c
OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Creating $(NAME)...$(RESET)"
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)Done!$(RESET)"

$(LIBFT):
	@echo "$(GREEN)Compiling libft...$(RESET)"
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus