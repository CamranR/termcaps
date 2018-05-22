/*
** EPITECH PROJECT, 2017
** my_getnbr.c
** File description:
** my_getnbr
*/

int my_getnbr(char *str)
{
	long nb = 0;
	int sign = 1;
	int i = 0;

	while (str[i] == '+' || str[i] == '-') {
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] != '\0') {
		if (str[i] >= '0' && str[i] <= '9') {
			nb *= 10;
			nb += str[i] - '0';
			i++;
		}
		else
			return (nb * sign);
	}
	return (nb >= 2147483647 && nb <= -2147483647 ? 0 : (nb * sign));
}
