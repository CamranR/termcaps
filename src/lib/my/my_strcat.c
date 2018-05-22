/*
** EPITECH PROJECT, 2017
** my_strcat.c
** File description:
** my_strcat
*/

int my_strlen(char const *);

char *my_strcat(char *dest, char const *src)
{
	int len = my_strlen(dest);
	int i = 0;

	while (src[i] != '\0') {
		dest[i + len] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}
