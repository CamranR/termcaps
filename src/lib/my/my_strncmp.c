/*
** EPITECH PROJECT, 2017
** my_strncmp.c
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
	int i = 0;

	while((s1[i] != '\0') && (s1[i] == s2[i]) && i < n-1) {
		i = i + 1;
	}
	if ((*s1 == '\0' && *s2 == '\0')||(n ==0))
		return (0);
	if (n == 1 || *s1 == '\0' || *s2 == '\0' || i == 0)
		return (s1[i] - s2[i]);
	else
		return (s1[i] - s2[i]);
}
