/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/ftp.h"

static const char *refs[] = {
	"USER", "PASS", "CWD", "CDUP", "QUIT",
	"DELE", "PWD", "PASV", "PORT", "HELP",
	"NOOP", "RETR", "STOR", "LIST", "TYPE",
	NULL,
};

static bool (*fcts[])(sess_t *, char *, net_t *) = {
	&cmd_user, &cmd_pass, &cmd_cwd,
	&cmd_cdup, &cmd_quit, &cmd_dele,
	&cmd_pwd, &cmd_pasv, &cmd_port,
	&cmd_help, &cmd_noop, &cmd_retr,
	&cmd_stor, &cmd_list, &cmd_type,
};

static bool is_full_space(char *line)
{
	size_t space_count = 0;

	for (size_t i = 0 ; i < strlen(line) ; ++i)
		if (line[i] != ' ' && line[i] != '\r' && line[i] != '\n')
			return (false);
		else if (line[i] == ' ')
			space_count++;
	return (space_count > 0);
}

static void print_unknown_command(sess_t *sess, net_t *client)
{
	if (sess->logged)
		dprintf(client->fd, "500 Unknown command.\n");
	else
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
}

bool commander(sess_t *sess, char *line, net_t *client)
{
	char *cmd = to_upper_case(get_arg(line, 0));
	int ret = -1;

	if (is_full_space(line)) {
		print_unknown_command(sess, client);
		return (true);
	}
	if (!strlen(cmd))
		return (true);
	for (size_t i = 0 ; refs[i] ; ++i)
		if (!strcmp(refs[i], cmd))
			ret = fcts[i](sess, line, client);
	if (ret == -1)
		print_unknown_command(sess, client);
	return (ret != 0);
}
