/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_pwd(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	dprintf(client->fd, "257 \"%s\" created.\n", sess->pathname);
	return (true);
}
