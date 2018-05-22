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

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -pedantic -I./src/include -g3

NAME	=	termcaps

CC	=	gcc

RM	=	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		@echo "$(GREEN)\t>> COMPILATION SUCCESS\n$(WHITE)"
		make re -C ./src/lib/my
		cc -o $(NAME) $(OBJ) -Lsrc/lib/my -lmy -lncurses
		@echo "$(YELLOW)\t>> LINKING SUCCESS\n$(WHITE)"

clean:
		rm -f $(OBJ)
		@echo "$(RED)\t>> DELETING BINAIRIES SUCCESS\n$(WHITE)"
		make clean -C ./src/lib/my
		@echo "$(RED)\t>> CLEANING LIB SUCCESS\n$(WHITE)"
		rm -f *.a
		@echo "$(RED)\t>> DELETING STATIC LIBRARY SUCCESS\n$(WHITE)"

fclean:		clean
		rm -f $(NAME)
		@echo "$(RED)\t>> DELETING EXECUTABLE SUCCESS\n$(WHITE)"
		make fclean -C ./src/lib/my
		@echo "$(RED)\t>> FCLEANING LIB SUCCESS\n$(WHITE)"
		rm -f *.a
		@echo "$(RED)\t>> DELETING STATIC LIBRARY SUCCESS\n$(WHITE)"

re:		fclean all
