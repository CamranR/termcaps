/*
** EPITECH PROJECT, 2017
** my_str_isupper.c
** File description:
** my_str_isupper
*/

int my_str_isupper(char const *str)
{
	int i = 0;
	char a = str[i];

	if (!str)
		return (0);
	while (str[i] != '\0') {
		a = str[i];
		if (a >= 'A' && a <= 'Z')
			i++;
		else
			return (0);
	}
	return (1);
}
