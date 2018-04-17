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
	"NOOP", "RETR", "STOR", "LIST", "AUTH",
	"TYPE", NULL,
};

static bool (*fcts[])(sess_t *, char *, net_t *) = {
	&cmd_user, &cmd_pass, &cmd_cwd,
	&cmd_cdup, &cmd_quit, &cmd_dele,
	&cmd_pwd, &cmd_pasv, &cmd_port,
	&cmd_help, &cmd_noop, &cmd_retr,
	&cmd_stor, &cmd_list, &cmd_auth,
	&cmd_type,
};

bool commander(sess_t *sess, char *line, net_t *client)
{
	char *cmd = to_upper_case(get_arg(line, 0));
	int ret = -1;

	if (!strlen(cmd))
		return (true);
	for (size_t i = 0 ; refs[i] ; ++i)
		if (!strcmp(refs[i], cmd))
			ret = fcts[i](sess, line, client);
	if (ret == -1)
		dprintf(client->fd, "500 Unknown command.\n");
	return (ret != 0);
}
