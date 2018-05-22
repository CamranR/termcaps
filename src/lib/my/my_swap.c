/*
** EPITECH PROJECT, 2017
** my_swap.c
** File description:
** my_swap
*/

void my_swap(int *a, int *b)
{
	int buffer = *a;

	*a = *b;
	*b = buffer;
}
