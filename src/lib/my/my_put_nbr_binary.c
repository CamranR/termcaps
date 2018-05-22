/*
** EPITECH PROJECT, 2017
** my_put_nbr_binary.c
** File description:
** my_put_nbr_binary
*/

#include "../../include/my.h"

int my_put_nbr_binary(unsigned int decimal)
{
	long tmp;
	char binary[65];
	int index = 0;
	int counter = 0;

	tmp = decimal;
	while (tmp != 0) {
		binary[index] = (tmp % 2) + '0';
		tmp /= 2;
		index++;
	}
	binary[index] = '\0';
	my_revstr(binary);
	counter = my_putstr(binary);
	return (counter);
}
