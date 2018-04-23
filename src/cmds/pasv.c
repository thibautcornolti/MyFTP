/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"
#include "../../include/passive.h"

bool cmd_pasv(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	start_passive_mode(sess);
	dprintf(client->fd, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\n",
	127, 0, 0, 1,
	ntohs(sess->pasv_listen.s_in.sin_port) / 256,
	ntohs(sess->pasv_listen.s_in.sin_port) % 256);
	dprintf(1, "port=%d\n", ntohs(sess->pasv_listen.s_in.sin_port));
	return (true);
}
