/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_help(sess_t *sess, char *line, net_t *client)
{
	(void) sess;
	(void) line;
	dprintf(client->fd, "214 Help message.\n");
	return (true);
}
