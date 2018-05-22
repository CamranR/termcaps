/*
** EPITECH PROJECT, 2017
** my_str_isprintable.c
** File description:
** my_str_isprintable
*/

int my_str_isprintable(char const *str)
{
	int i = 0;
	char a = str[i];

	if (!str)
		return (0);
	while (str[i] != '\0') {
		a = str[i];
		if (a >= 32 && a <= 126)
			i++;
		else
			return (0);
	}
	return (1);
}
