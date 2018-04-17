/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_cdup(sess_t *sess, char *line, net_t *client)
{
	size_t last_slash = 0;

	(void) line;
	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	for (size_t i = 0 ; sess->pathname[i] ; ++i) {
		if (sess->pathname[i] == '/')
			last_slash = i;
	}
	if (last_slash > 0)
		sess->pathname[last_slash] = 0;
	else
		sess->pathname[1] = 0;
	dprintf(client->fd, "200 Command okay.\n");
	return (true);
}
