/*
** EPITECH PROJECT, 2017
** my_strncpy.c
** File description:
** my_strncpy
*/

int my_strlen (char const *);

char *my_strncpy(char *dest, char const *src, int n)
{
	int len = my_strlen(src);
	int i = 0;

	if (len  <= n + 1)
		n = my_strlen(src);
	while (i <= n) {
		dest[i] = src[i];
		i++;
	}
	if (n > len)
		dest[len] = '\0';
	return (dest);
}
