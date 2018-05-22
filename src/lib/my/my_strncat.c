/*
** EPITECH PROJECT, 2017
** my_strncat.c
** File description:
** my_strncat
*/

int my_strlen(char const *);

char *my_strncat(char *dest, char const *src, int nb)
{
	int len = my_strlen(dest);
	int i = 0;

	for (; i < nb && src[i] != '\0' ; i++)
		dest[len + i] = src[i];
	dest[len + i] = '\0';

	return (dest);
}
