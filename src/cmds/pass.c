/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_pass(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	if (!sess->user)
		dprintf(client->fd, "332 Need account for login.\n");
	else if (!strcmp(sess->user, "anonymous") ||
		!strcmp(sess->user, "Anonymous")) {
			sess->logged = true;
			dprintf(client->fd, "230 User logged in, proceed.\n");
		}
	else
		dprintf(client->fd, "530 Login incorrect.\n");
	return (true);
}
