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

void ctrl_a(termline_s *line)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	while (line->pos > 0) {
		write(1, "\033[D", 4);
		line->pos -= 1;
	}
}

void ctrl_b(termline_s *line)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (line->pos > 0) {
		write(1, "\033[D", 4);
		line->pos -= 1;
	}
}

void ctrl_c(termline_s *line, char **env)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	write(1, "\n", 1);
	prompt(env);
	free (line->str);
	line->str = calloc(1, 1);
	line->pos = 0;
	line->len = 0;
}

char *ctrl_d(termline_s *line, char **env)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (line->len == 0) {
		write(1, "exit\n", 5);
//		write(1, "\033c", 3);	// a virer une fois que tu restore le term
		return (NULL);
	} else if (line->pos < line->len) {
		tputs(line->del, 0, write_char);
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	} else {
		write(1, "\n", 1);
		prompt(env);
		write(1, line->str, line->len);
	}
	return ("ok");
}

void ctrl_e(termline_s *line)
{
	while (line->pos != line->len) {
		write(1, "\033[C", 4);
		line->pos += 1;
	}
}

void ctrl_f(termline_s *line)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (line->pos < line->len) {
		write(1, "\033[C", 4);
		line->pos += 1;
	}
}

void ctrl_h(termline_s *line)
{
	if (line->len > 0 && line->pos > 0) {
		line->pos -= 1;
		tputs(line->del, 0, write_char);
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	} else
		write(1, "\033[C", 4);
}

void ctrl_k(termline_s *line, char **save)
{
	write(1, "\033[A", 4);
	if (*save != NULL) {
		free (*save);
		*save = calloc(1, 1);
	}
	while (line->pos < line->len) {
		tputs(line->del, 0, write_char);
		*save = add_char(*save, line->str[line->pos], strlen(*save) + 1, strlen(*save));
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	}
}

void ctrl_l(termline_s *line, char **env)
{
	tputs(line->clear, 0, write_char);
	prompt(env);
	write(1, line->str, line->len);
}

void ctrl_u(termline_s *line, char **save)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (*save != NULL)
		free (*save);
	if (line->str != NULL) {
		*save = strdup(line->str);
		free(line->str);
		line->str = calloc(1, 1);
	}
	while (line->pos > 0) {
		write(1, "\033[D", 4);
		line->pos -= 1;
	}
	while (line->len > 0) {
		tputs(line->del, 0, write_char);
		line->len -= 1;
	}
}

void ctrl_w(termline_s *line, char **save)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (*save != NULL) {
		free (*save);
		*save = calloc(1, 1);
	}
	while (line->pos > 0) {
		line->pos -= 1;
		write(1, "\033[D", 4);
		tputs(line->del, 0, write_char);
		*save = add_char(*save, line->str[line->pos], strlen(*save) + 1, 0);
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	}
}

void ctrl_y(termline_s *line, char **save)
{
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (*save != NULL) {
		write (1, *save, strlen(*save));
		for (int i = 0; (*save)[i]; i++) {
			line->len += 1;
			line->str = add_char(line->str, (*save)[i], line->len, line->pos);
			line->pos += 1;
		}
	}
}

void keys_control(char *buffer, termline_s *line)
{
	switch (buffer[2]) {
		case 65:
			write(1, "\033[B", 4);
			break;
		case 66:
			write(1, "\033[A", 4);
			break;
		case 67:
			if (line->pos < line->len)
				line->pos += 1;
			else
				write(1, "\033[D", 4);
			break;
		case 68:
			if (line->pos > 0)
				line->pos -= 1;
			else
				write(1, "\033[C", 4);
	}
}

void key_suppr(termline_s *line)
{
	if (line->pos < line->len) {
		tputs(line->del, 0, write_char);
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	}
	for (int i = 0; i < 4; i++) {
		write(1, "\033[D", 4);
		tputs(line->del, 0, write_char);
	}
}

void key_delete(termline_s *line)
{
	if (line->len > 0 && line->pos > 0) {
		line->pos -= 1;
		write(1, "\033[D", 4);
		tputs(line->del, 0, write_char);
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	}
}

termline_s *init_line(void)
{
	termline_s *line = malloc (sizeof(termline_s) * 1);

	line->str = calloc(1, 1);
	if ((line->clear = tgetstr("cl", NULL)) == NULL)
		return (NULL);
	if ((line->del = tgetstr("dc", NULL)) == NULL)
		return (NULL);
	line->len = 0;
	line->pos = 0;
	return (line);
}

char *get_key(char **env)
{
	char buffer[3];
	termline_s *line = init_line();
	static char *save = NULL;

	prompt(env);
	save = calloc(1, 1);
	while (1) {
		write(1, "\033[3g", 5);
		read(0, buffer, 3);
		//printf("\n%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
		if (buffer[0] == 1)
			ctrl_a(line);
		else if (buffer [0] == 2)
			ctrl_b(line);
		else if (buffer[0] == 3)
			ctrl_c(line, env);
		else if (buffer[0] == 4) {
			if (ctrl_d(line, env) == NULL)
				return (NULL);
		} else if (buffer[0] == 5)
			ctrl_e(line);
		else if (buffer [0] == 6)
			ctrl_f(line);
		else if (buffer [0] == 8)
			ctrl_h(line);
		// else if (buffer[0] == 9)
		// 	//	place autocomplete here!!!!
		else if (buffer[0] == 10)
			return (line->str);
		else if (buffer[0] == 11)
			ctrl_k(line, &save);
		else if (buffer[0] == 12)
			ctrl_l(line, env);
		else if (buffer[0] == 21)
			ctrl_u(line, &save);
		else if (buffer[0] == 23)
			ctrl_w(line, &save);
		else if (buffer[0] == 25)
			ctrl_y(line, &save);
		else if (buffer[0] == 27)
			keys_control(buffer, line);
		else if (buffer[0] == 126 && buffer[2] == 51)
			key_suppr(line);
		else if (buffer[0] >= 32 && buffer[0] <= 126) {
			line->len += 1;
			line->str = add_char(line->str, buffer[0], line->len, line->pos);
			line->pos += 1;
		} else if (buffer[0] == 127)
			key_delete(line);
		else if (buffer[0] != 15 && buffer[0] != 7 && buffer[0] != 14) {
			write(1, "\033[D", 4);
			tputs(line->del, 0, write_char);
		}
	}
}

int	main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		char **env)
{
	char	*name_term;
	char	*insert_mode;
	struct	termios term;
	struct	termios backup;
	char	*blink;

	get_term_size();
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	if (tcgetattr(0, &backup) == -1)
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
	if ((blink = tgetstr("vb", NULL)) == NULL)		//totally
		return (-1);					//useless
	while (1) {
		tputs(blink, 0, write_char);			//but it's a feature
		if (get_key(env) == NULL)
			break;
	}
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	//write(1, "\33[H\33[2J", 8);
	return (0);
}
