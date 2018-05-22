/*
** EPITECH PROJECT, 2017
** my_str_isnum.c
** File description:
** my_str_isnum
*/

int my_str_isnum(char const *str)
{
	int i = 0;
	char a = str[i];

	while (str[i] != '\0') {
		a = str[i];
		if (a >= '0' && a <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
