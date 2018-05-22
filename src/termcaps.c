/*
** EPITECH PROJECT, 2018
** 42sh_termcaps
** File description:
** termcaps
*/

#include "my.h"

#define ESC 27

#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

int	write_char(int c)
{
	write(1, &c, 1);
	return (0);
}

void	get_term_size(void)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

//	printf ("lines %d\n", w.ws_row);
//	printf ("columns %d\n", w.ws_col);
}

void prompt(char **env)
{
	char *host = NULL;
	char *pwd = getcwd(NULL, 0);

	for (int i = 0; env[i] != NULL; i++) {
		if (my_strncmp(env[i], "LOGNAME=", 8) == 0) {
			host = env[i];
			host += 8;
		}
	}
	if (isatty(0) == 1) {
		printf("%s%s%s:%s%s%s> %s", UNDERLINE, RED, host, WHITE,
				GREEN, pwd, WHITE);
		fflush(stdout);
	}
	free(pwd);
}

void get_cursor_position(int *col, int *rows)
{
	int a = 0;
	int i = 0;
	char buf[4];
	//int fd = open(".size", O_CREAT & O_WRONLY);

	// write(fd, "\033[6n", 4);
	// read(fd, buf, 4);
	write(1, "\033[6n", 4);
	read(1, buf, 4);
	while (buf[i]) {
		if (buf[i] >= 48 && buf[i] <= 57) {
			if (a == 0)
				*rows = atoi(&buf[i]);
			else
				*col = atoi(&buf[i]);
			a++;
		}
		i++;
	}
	//close(fd);
}

int	get_key(char **env)
{
	char buffer[3];
	char *clear;
	char *delete;
	static int len = 0;
	static int pos = 0;
	int col = 0;
	int rows = 0;

	if ((clear = tgetstr("cl", NULL)) == NULL)
		return (-1);
	if ((delete = tgetstr("dc", NULL)) == NULL)
		return (-1);
	get_cursor_position(&col, &rows);
	col += 1;
	prompt(env);
	while (1) {
		read(0, buffer, 3);
		if (buffer[0] == 27) {
			if (buffer[2] == 65) {
				write(1, "\033[B", 4);
			}
			if (buffer[2] == 66) {
				write(1, "\033[A", 4);
			}
			if (buffer[2] == 67) {
				if (pos < len)
					pos += 1;
				else
					write(1, "\033[D", 4);
			}
			if (buffer[2] == 68) {
				if (pos > 1)
					pos -= 1;
				else
					write(1, "\033[C", 4);
			}
		} else if (buffer[0] == 3) {
			printf("\n");
			break;
		} else if (buffer[0] == 4) {
			write(1, "exit\n", 5);
			exit(0);
		} else if (buffer[0] == 12) {
			tputs(clear, 0, write_char);
			break;
		} else if (buffer[0] == 10) {
			len = 0;
			pos = 0;
			break;
		// } else if (buffer[0] == 126 && buffer[2] == 51) {
		// 	if (len > 1 && pos < len) {
		// 		tputs(delete, 0, write_char);
		// 		len -= 1;
		// 	}
		} else if (buffer[0] >= 32 && buffer[0] <= 126) {
			if (len == pos) {
				len += 1;
			}
			pos += 1;
		} else if (buffer[0] == 127) {
			if (len > 1 && pos > 0 ) {
				write(1, "\033[D", 4);
				tputs(delete, 0, write_char);
				len -= 1;
				pos -= 1;
			}
		}
	}
	return (0);
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		char **env)
{
	char	*name_term;
	char *insert_mode;
	struct termios term;

	get_term_size();
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);

	term.c_lflag &= ~(ICANON);
	term.c_lflag &= (ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	if ((insert_mode = tgetstr("im", NULL)) == NULL)
		return (-1);
	tputs(insert_mode, 0, write_char);
	while (1)
		get_key(env);
	return (0);
}
