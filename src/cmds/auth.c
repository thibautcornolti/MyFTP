/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_auth(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	dprintf(client->fd, "no auth mdr.\n");
	return (true);
}
