/*
** EPITECH PROJECT, 2017
** my_compute_square_root.c
** File description:
** my_compute_square_root
*/

int check_error(int i)
{
	if (i < 1)
		return (0);
	else
		return (i);
}

int my_compute_square_root(int nb)
{
	int i = nb;

	if (nb < 0)
		return (0);
	while (i >= 0) {
		if (i * i == nb) {
			check_error(i);
			return (i);
		}
		i--;
	}
	return (0);
}
