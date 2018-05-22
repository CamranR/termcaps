/*
** EPITECH PROJECT, 2017
** my_putstr.c
** File description:
** my_putstr
*/

void my_putchar(char);

int my_putstr(char const *str)
{
	int counter = 0;
	int i = 0;

	while (str[i] != '\0') {
		my_putchar(str[i]);
		counter++;
		i++;
	}
	return (counter);
}
