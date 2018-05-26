##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## bootstrap_printf
##

RED     =       \033[01;31m
YELLOW  =       \033[01;32m
GREEN   =       \033[01;33m
WHITE   =       \033[0m
CYAN            = \033[01;34m

SRC	=	./src/termcaps.c			\
		./src/read_file.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -pedantic -I./src/include -g3

NAME	=	termcaps

CC	=	gcc

RM	=	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		@echo "$(GREEN)\t>> COMPILATION SUCCESS\n$(WHITE)"
		cc -o $(NAME) $(OBJ) -lncurses
		@echo "$(YELLOW)\t>> LINKING SUCCESS\n$(WHITE)"

clean:
		rm -f $(OBJ)
		@echo "$(RED)\t>> DELETING BINAIRIES SUCCESS\n$(WHITE)"

fclean:		clean
		rm -f $(NAME)
		@echo "$(RED)\t>> DELETING EXECUTABLE SUCCESS\n$(WHITE)"

re:		fclean all
