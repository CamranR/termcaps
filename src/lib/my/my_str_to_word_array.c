/*
** EPITECH PROJECT, 2017
** my_str_to_word_array.c
** File description:
** my_str_to_word_array
*/

#include "../../include/my.h"
#include <stdlib.h>
#include <stdio.h>

int is_alphanum(char c, char delim)
{
	if (c == delim)
		return (0);
	else
		return (1);
}

int word_count(char const *str, char delim)
{
	int wc = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == delim) {
			wc++;
		while (str[i] != delim && str[i + 1] != '\0')
			i++;
		}
	}
	return (wc + 2);
}

int word_len(char const *str, char delim)
{
	int i = 0;
	int word_ln = 0;

	while (str[i] != delim || str[i] != '\0') {
		word_ln++;
		i++;
	}
	return(word_ln + 1);
}

char **my_str_to_word_array(char const *str, char delim)
{
	int j = 0;
	int x = 0;
	int wc = word_count(str, delim);
	int wl = word_len(str, delim);
	int tmp = 0;
	char **dest = malloc(sizeof(char *) * (wc + 1));

	for (int i = 0; i <= wc && my_strlen(str) >= tmp;) {
		wl = word_len(str + tmp, delim);
		dest[i] = malloc(sizeof(char) * wl);
		while (is_alphanum(str[x], delim) == 1)
			dest[i][j++] = str[x++];
		if (is_alphanum(str[x++], delim) == 0) {
			dest[i++][j] = '\0';
			j = 0;
		}
		tmp += wl;
	}
	dest[wc - 1] = NULL;
	return (dest);
}