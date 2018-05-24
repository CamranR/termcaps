/*
** EPITECH PROJECT, 2018
** 42sh_termcaps
** File description:
** termcaps
*/

#include "my.h"

#define ESC 27

#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

int write_char(int c)
{
	write(1, &c, 1);
	return (0);
}

void get_term_size(void)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
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
}

char *add_char(char *str, char c, int len, int pos)
{
	char *next = calloc(1, len + 1);
	int i = 0;

	for (; i < pos; i++)
		next[i] = str[i];
	next[i++] = c;
	for (int j = i - 1; i < len; i++)
		next[i] = str[j++];
	if (str != NULL)
		free(str);
	return (next);
}

char *del_char(char *str, int len, int pos)
{
	char *next = calloc(1, len);
	int i = 0;

	for (; i < pos; i++)
		next[i] = str[i];
	for (int j = i + 1; i < len; i++)
		next[i] = str[j++];
	if (str != NULL)
		free(str);
	return (next);
}

int get_key(char **env)
{
	char buffer[3];
	char *str = calloc(1, 1);
	char *clear;
	char *delete;
	static char *save = NULL;
	int len = 0;
	int pos = 0;

	if ((clear = tgetstr("cl", NULL)) == NULL)
		return (-1);
	if ((delete = tgetstr("dc", NULL)) == NULL)
		return (-1);
	prompt(env);
	save = calloc(1, 1);
	while (1) {
		write(1, "\033[3g", 5);
		read(0, buffer, 3);
		if (buffer[0] == 1) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			while (pos > 0) {
				write(1, "\033[D", 4);
				pos -= 1;
			}
		} else if (buffer [0] == 2) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			if (pos > 0) {
				write(1, "\033[D", 4);
				pos -= 1;
			}
		} else if (buffer[0] == 3) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			printf("\n");
			break;
		} else if (buffer[0] == 4) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			if (len == 0) {
				write(1, "exit\n", 5);
//				write(1, "\033c", 3);	// a virer une fois que tu restore le term
				return (-42);
			} else if (pos < len) {
				tputs(delete, 0, write_char);
				str = del_char(str, len, pos);
				len -= 1;
			} else {
				write(1, "\n", 1);
				prompt(env);
				write(1, str, len);
			}
		} else if (buffer[0] == 5) {
			while (pos != len) {
				write(1, "\033[C", 4);
				pos += 1;
			}
		} else if (buffer [0] == 6) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			if (pos < len) {
				write(1, "\033[C", 4);
				pos += 1;
			}
		} else if (buffer [0] == 8) {
			if (len > 0 && pos > 0) {
				pos -= 1;
				tputs(delete, 0, write_char);
				str = del_char(str, len, pos);
				len -= 1;
			} else
				write(1, "\033[C", 4);
		} else if (buffer[0] == 9) {
				//	place autocomplete here!!!!
		} else if (buffer[0] == 10) {
			break;
		} else if (buffer[0] == 11) {
			write(1, "\033[A", 4);
			if (save != NULL) {
				free (save);
				save = calloc(1, 1);
			}
			while (pos < len) {
				tputs(delete, 0, write_char);
				save = add_char(save, str[pos], strlen(save), strlen(save));
				str = del_char(str, len, pos);
				len -= 1;
			}
		} else if (buffer[0] == 12) {
			tputs(clear, 0, write_char);
			prompt(env);
			write(1, str, len);
		} else if (buffer[0] == 21) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			if (save != NULL)
				free (save);
			if (str != NULL) {
				save = strdup(str);
				free(str);
				str = calloc(1, 1);
			}
			while (pos > 0) {
				write(1, "\033[D", 4);
				pos -= 1;
			}
			while (len > 0) {
				tputs(delete, 0, write_char);
				len -= 1;
			}
		} else if (buffer[0] == 23) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			if (save != NULL) {
				free (save);
				save = calloc(1, 1);
			}
			while (pos > 0) {
				pos -= 1;
				write(1, "\033[D", 4);
				tputs(delete, 0, write_char);
				save = add_char(save, str[pos], strlen(save) + 1, 0);
				str = del_char(str, len, pos);
				len -= 1;
			}
		} else if (buffer[0] == 25) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
			if (save != NULL) {
				write (1, save, strlen(save));
				for (int i = 0; save[i]; i++) {
					len += 1;
					str = add_char(str, save[i], len, pos);
					pos += 1;
				}
			}
		} else if (buffer[0] == 27) {
				if (buffer[2] == 65) {
					write(1, "\033[B", 4);
					//place history up here!!!
				}
				if (buffer[2] == 66) {
					write(1, "\033[A", 4);
					//place history down here!!!
				}
				if (buffer[2] == 67) {
					if (pos < len)
						pos += 1;
					else
						write(1, "\033[D", 4);
				}
				if (buffer[2] == 68) {
					if (pos > 0)
						pos -= 1;
					else
						write(1, "\033[C", 4);
				}
		} else if (buffer[0] == 126 && buffer[2] == 51) {
			if (pos < len) {
				tputs(delete, 0, write_char);
				str = del_char(str, len, pos);
				len -= 1;
			}
			for (int i = 0; i < 4; i++) {
				write(1, "\033[D", 4);
				tputs(delete, 0, write_char);
			}
		} else if (buffer[0] >= 32 && buffer[0] <= 126) {
			len += 1;
			str = add_char(str, buffer[0], len, pos);
			pos += 1;
		} else if (buffer[0] == 127) {
			if (len > 0 && pos > 0) {
				pos -= 1;
				write(1, "\033[D", 4);
				tputs(delete, 0, write_char);
				str = del_char(str, len, pos);
				len -= 1;
			}
		} else if (buffer[0] != 15 && buffer[0] != 7 && buffer[0] != 14) {
			write(1, "\033[D", 4);
			tputs(delete, 0, write_char);
		}
	}
	return (0);
}

int check_terminal(struct termios *term, struct termios *backup)
{
	char *name_term = NULL;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, term) == -1)
		return (-1);
	if (tcgetattr(0, backup) == -1)
		return (-1);
	(*term).c_lflag &= ~(ICANON);
	(*term).c_lflag &= (ECHO);
	(*term).c_cc[VMIN] = 1;
	(*term).c_cc[VTIME] = 0;
	return (0);
}

int run_term(char **env, char *insert_mode)
{
	char *blink = NULL;

	tputs(insert_mode, 0, write_char);
	if ((blink = tgetstr("vb", NULL)) == NULL)
		return (-1);
	while (1) {
		tputs(blink, 0, write_char);
		if (get_key(env) == -42)
			return (1);
	}
	return (0);
}

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		char **env)
{
	char *insert_mode = NULL;
	struct termios term;
	struct termios backup;

	get_term_size();
	if (check_terminal(&term, &backup) == -1)
		return (84);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (84);
	if ((insert_mode = tgetstr("im", NULL)) == NULL)
		return (84);
	run_term(env, insert_mode);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (84);
	return (0);
}