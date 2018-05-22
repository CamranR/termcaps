/*
** EPITECH PROJECT, 2017
** my_str_islower.c
** File description:
** my_str_islower
*/

int my_str_islower(char const *str)
{
	int i = 0;
	char a = str[i];

	if (!str)
		return (0);
	while (str[i] != '\0') {
		a = str[i];
		if (a >= 'a' && a <= 'z')
			i++;
		else
			return (0);
	}
	return (1);
}
