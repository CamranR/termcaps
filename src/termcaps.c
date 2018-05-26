/*
** EPITECH PROJECT, 2018
** 42sh_termcaps
** File description:
** termcaps
*/

#include "my.h"

int write_char(int c)
{
	write(1, &c, 1);
	return (0);
}

void prompt(char **env)
{
	char *host = NULL;
	char *pwd = getcwd(NULL, 0);

	for (int i = 0; env[i] != NULL; i++) {
		if (strncmp(env[i], "LOGNAME=", 8) == 0) {
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

void free_termline(termline_s *line)
{
	free (line->str);
	free (line);
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
	line->check = 1;
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	while (line->pos > 0) {
		write(1, "\033[D", 4);
		line->pos -= 1;
	}
}

void ctrl_b(termline_s *line)
{
	line->check = 1;
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (line->pos > 0) {
		write(1, "\033[D", 4);
		line->pos -= 1;
	}
}

void ctrl_c(termline_s *line, char **env)
{
	line->check = 1;
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
	line->check = 1;
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (line->len == 0) {
		free_termline(line);
		write(1, "exit\n", 5);
		system("reset");
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
	line->check = 1;
	while (line->pos != line->len) {
		write(1, "\033[C", 4);
		line->pos += 1;
	}
}

void ctrl_f(termline_s *line)
{
	line->check = 1;
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (line->pos < line->len) {
		write(1, "\033[C", 4);
		line->pos += 1;
	}
}

void ctrl_h(termline_s *line)
{
	line->check = 1;
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
	line->check = 1;
	write(1, "\033[A", 4);
	if (*save != NULL) {
		free (*save);
		*save = calloc(1, 1);
	}
	while (line->pos < line->len) {
		tputs(line->del, 0, write_char);
		*save = add_char(*save, line->str[line->pos],
		strlen(*save) + 1, strlen(*save));
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	}
}

void ctrl_l(termline_s *line, char **env)
{
	line->check = 1;
	tputs(line->clear, 0, write_char);
	prompt(env);
	write(1, line->str, line->len);
}

void ctrl_u(termline_s *line, char **save)
{
	line->check = 1;
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
	line->check = 1;
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
		*save = add_char(*save, line->str[line->pos],
		strlen(*save) + 1, 0);
		line->str = del_char(line->str, line->len, line->pos);
		line->len -= 1;
	}
}

void ctrl_y(termline_s *line, char **save)
{
	line->check = 1;
	write(1, "\033[D", 4);
	tputs(line->del, 0, write_char);
	if (*save != NULL) {
		write (1, *save, strlen(*save));
		for (int i = 0; (*save)[i]; i++) {
			line->len += 1;
			line->str = add_char(line->str, (*save)[i], line->len,
			line->pos);
			line->pos += 1;
		}
	}
}

void keys_control(char *buffer, termline_s *line)
{
	line->check = 1;
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
	line->check = 1;
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
	line->check = 1;
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

void check_one_sub(char **save)
{
	if (*save != NULL)
		free(*save);
}

char *check_one(char buffer[3], char **save, termline_s *line, char **env)
{
	if (buffer[0] == 1)
		ctrl_a(line);
	else if (buffer [0] == 2)
		ctrl_b(line);
	else if (buffer[0] == 3)
		ctrl_c(line, env);
	else if (buffer[0] == 4) {
		if (ctrl_d(line, env) == NULL) {
			check_one_sub(save);
			return (NULL);
		}
	}
	return ("ok");
}

termline_s *check_two(char buffer[3], char **save, termline_s *line, char **env)
{
	if (buffer[0] == 5)
		ctrl_e(line);
	else if (buffer [0] == 6)
		ctrl_f(line);
	else if (buffer [0] == 8)
		ctrl_h(line);
	// else if (buffer[0] == 9)
	// 	//	place autocomplete here!!!!
	else if (buffer[0] == 10)
		return (line);
	else if (buffer[0] == 11)
		ctrl_k(line, save);
	else if (buffer[0] == 12)
		ctrl_l(line, env);
	else if (buffer[0] == 21)
		ctrl_u(line, save);
	return (NULL);
}

void check_three(char buffer[3], char **save, termline_s *line)
{
	if (buffer[0] == 23)
		ctrl_w(line, save);
	else if (buffer[0] == 25)
		ctrl_y(line, save);
	else if (buffer[0] == 27)
		keys_control(buffer, line);
	else if (buffer[0] == 126 && buffer[2] == 51)
		key_suppr(line);
}

void check_four(char buffer[3], termline_s *line)
{
	if (buffer[0] >= 32 && buffer[0] <= 126) {
		line->len += 1;
		line->str = add_char(line->str, buffer[0], line->len,
		line->pos);
		line->pos += 1;
	} else if (buffer[0] == 127)
		key_delete(line);
	else if (buffer[0] != 15 && buffer[0] != 7 && buffer[0] != 14) {
		write(1, "\033[D", 4);
		tputs(line->del, 0, write_char);
	}
}

termline_s *get_key(char **env, char **save)
{
	char buffer[3];
	termline_s *line = init_line();

	prompt(env);
	while (1) {
		write(1, "\033[3g", 5);
		read(0, buffer, 3);
		line->check = 0;
		if (check_one(buffer, save, line, env) == NULL)
			return (NULL);
		if (line->check == 1)
			continue;
		if (check_two(buffer, save, line, env) != NULL)
			return (line);
		if (line->check == 1)
			continue;
		check_three(buffer, save, line);
		if (line->check == 1)
			continue;
		check_four(buffer, line);
	}
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
	termline_s *command_line;
	char *cmd;
	static char *save = NULL;

	tputs(insert_mode, 0, write_char);
	while (1) {
		if (save == NULL)
			save = calloc(1, 1);
		if ((command_line = get_key(env, &save)) == NULL)
			break;
		else {
			cmd = strdup(command_line->str);
			free_termline (command_line);
			free(cmd);	// here place quentin part instead of free
		}
	}
	return (0);
}

void run_term_no_env(char **env)
{
	int vale = 0;
	char *geted = NULL;
	size_t n;

	while (1) {
		prompt(env);
		if ((vale = getline(&geted, &n, stdin)) < 0)
			break;
	}
}

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av,
		char **env)
{
	char *insert_mode = NULL;
	struct termios term;
	struct termios backup;

	if (env[0]) {
	if (check_terminal(&term, &backup) == -1)
		return (84);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (84);
	if ((insert_mode = tgetstr("im", NULL)) == NULL)
		return (84);
	run_term(env, insert_mode);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (84);
	} else {
		run_term_no_env(env);
	}
	return (0);
}
