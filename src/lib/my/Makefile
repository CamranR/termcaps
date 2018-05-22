##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

RED     =       \033[01;31m
YELLOW  =       \033[01;32m
GREEN   =       \033[01;33m
WHITE   =       \033[0m
CYAN            = \033[01;34m

SRC=			my_compute_power_rec.c	 \
			my_compute_square_root.c \
			my_find_prime_sup.c	 \
			my_getnbr.c		 \
			my_isneg.c		 \
			my_is_prime.c		 \
			my_putchar.c		 \
			my_put_nbr.c		 \
			my_put_unsigned_nbr.c	 \
			my_putstr.c		 \
			my_revstr.c		 \
			my_showmem.c		 \
			my_showstr.c		 \
			my_strdup.c		 \
			my_sort_int_array.c	 \
			my_strcat.c		 \
			my_strcmp.c		 \
			my_strncmp.c		 \
			my_strcpy.c		 \
			my_str_isalpha.c	 \
			my_str_islower.c	 \
			my_str_isnum.c		 \
			my_str_isprintable.c	 \
			my_str_isupper.c	 \
			my_strlen.c		 \
			my_strlowcase.c		 \
			my_strncat.c		 \
			my_strncmp.c		 \
			my_strncpy.c		 \
			my_strstr.c		 \
			my_strupcase.c		 \
			my_swap.c		 \
			my_put_nbr_base.c	 \
			my_put_nbr_binary.c	 \
			my_put_pointer.c	 \
			my_printf/my_printf.c	 \
			my_printf/print_fct.c	 \
			my_printf/print_fct2.c	 \
			my_printf/print_fct3.c	 \
			my_printf/print_fct4.c	 \
			my_str_to_word_array.c	 \

OBJ=			$(SRC:.c=.o)

CFLAGS=			-W -Wall -Wextra -Werror -pedantic -g3

NAME=			libmy.a

CC=			gcc

RM=			rm -f


all: 			$(NAME)

$(NAME): 		$(OBJ)
			@echo "$(GREEN)\t>> COMPILATION SUCCESS\n$(WHITE)"
			ar rc $(NAME) $(OBJ)
			@echo "$(YELLOW)\t>> STATIC LIBRARY CREATION SUCCESS\n$(WHITE)"
			ranlib $(NAME)
			@echo "$(YELLOW)\t>> RANLIB SUCCESS\n$(WHITE)"

clean:
			rm -f $(OBJ)
			@echo "$(RED)\t>> DELETING BINAIRIES SUCCESS\n$(WHITE)"

fclean: 		clean
			rm -f $(NAME)
			@echo "$(RED)\t>> DELETING STATIC LIBRARY SUCCESS\n$(WHITE)"

re:			fclean all
