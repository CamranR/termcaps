/*
** EPITECH PROJECT, 2017
** my_revstr.c
** File description:
** my_revstr
*/

int my_strlen(char const *);

void my_putchar(char);

char *my_revstr(char *str)
{
	int len = my_strlen(str) - 1;
	int i = 0;
	int x = 0;
	char tmp[len];

	while (str[i] != '\0') {
		tmp[i] = str[len -i];
		i++;
	}
	tmp[i] = '\0';
	while (tmp[x] != '\0') {
		str[x] = tmp[x];
		x++;
	}
	str[len + 1] = '\0';
	return (str);
}
