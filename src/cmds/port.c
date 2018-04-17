/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_port(sess_t *sess, char *line, net_t *client)
{
	(void) sess;
	(void) line;
	dprintf(client->fd, "331 User name okay, need password.\n");
	return (true);
}
