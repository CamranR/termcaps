/*
** EPITECH PROJECT, 2017
** my_strupcase.c
** File description:
** my_strupcase
*/

int my_strlen(char const *);

char *my_strupcase(char *str)
{
	int i = 0;

	while (i <= my_strlen(str)) {
		if (str[i] > 96 && str[i] < 123)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}
