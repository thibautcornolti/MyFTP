/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_noop(sess_t *sess, char *line, net_t *client)
{
	(void) sess;
	(void) line;
	dprintf(client->fd, "200 Command okay.\n");
	return (true);
}
