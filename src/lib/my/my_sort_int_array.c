/*
** EPITECH PROJECT, 2017
** my_sort_int_array.c
** File description:
** my_sort_int_array.c
*/

void my_swap(int *, int *);

void my_sort_int_array(int *array, int size)
{
	int i = 0;

	while (i <= size) {
		if (array[i] > array[i + 1]) {
			my_swap(&array[i], &array[i + 1]);
			my_sort_int_array(array, size);
		}
		i++;
	}
}
