/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_quit(sess_t *sess, char *line, net_t *client)
{
	(void)sess;
	(void)line;
	dprintf(client->fd, "221 Goodbye.\n");
	return (false);
}
