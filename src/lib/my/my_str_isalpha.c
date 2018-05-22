/*
** EPITECH PROJECT, 2017
** my_str_isalpha.c
** File description:
** my_str_isalpha
*/

int my_str_isalpha(char const *str)
{
	int i = 0;
	char a = str[i];

	if (!str)
		return (0);
	while (str[i] != '\0') {
		a = str[i];
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
			i++;
		else
			return (0);
	}
	return (1);
}
