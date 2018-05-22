/*
** EPITECH PROJECT, 2017
** my_isneg.c
** File description:
** my_isneg
*/

void my_putchar(char);

int my_isneg(int n)
{
	if (n >= 0) {
		my_putchar('P');
		my_putchar('\n');
	} else if (n < 0) {
		my_putchar('N');
		my_putchar('\n');
	}
	return (0);
}
