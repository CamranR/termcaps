/*
** EPITECH PROJECT, 2018
** 42sh_history
** File description:
** read_file
*/

#include "my.h"

char	*read_file(char *path)
{
	FILE 		*fd = fopen(path, "rb");
	long 		fsize;
	char 		*string;

	fseek(fd, 0, SEEK_END);
	fsize = ftell(fd);
	rewind(fd);
	string = malloc(fsize + 1);
	fread(string, fsize, 1, fd);
	fclose(fd);
	string[fsize] = 0;
	return (string);
}