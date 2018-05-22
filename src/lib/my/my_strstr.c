/*
** EPITECH PROJECT, 2017
** my_strstr.c
** File description:
** my_strstr
*/

#include <stdlib.h>
#include "../../include/my.h"

char *my_strstr(char const *str, char const *to_find)
{
	int x;
	int y = 0;

	if (str[0] == '\0' && to_find[0] == '\0')
		return ("");
	if (my_strlen(to_find) > my_strlen(str))
		return (NULL);
	for (int i = 0; str[i] != '\0'; i++) {
		x = i;
		y = 0;
		while (str[x] == to_find[y] && str[x] != '\0') {
			x++;
			y++;
		}
		if (to_find[y] == '\0')
			return ((char *) &str[i]);
	}
	return (NULL);
}
