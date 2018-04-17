/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_user(sess_t *sess, char *line, net_t *client)
{
	if (sess->logged)
		dprintf(client->fd, "230 User logged in, proceed.\n");
	else {
		free(sess->user);
		sess->user = get_arg(line, 1);
		dprintf(client->fd, "331 User name okay, need password.\n");
	}
	return (true);
}
