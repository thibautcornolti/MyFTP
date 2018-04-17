/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

static void cmd_pasv_print(sess_t *sess, net_t *client)
{
	dprintf(client->fd, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\n",
		127, 0, 0, 1,
		ntohs(sess->pasv_listen.s_in.sin_port) / 256,
		ntohs(sess->pasv_listen.s_in.sin_port) % 256);
	dprintf(1, "port=%d\n", ntohs(sess->pasv_listen.s_in.sin_port));
}

bool cmd_pasv(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	if (!create_socket(&sess->pasv_listen) ||
		!bind_socket(0, &sess->pasv_listen))
		return (false);
	cmd_pasv_print(sess, client);
	if (!listen_socket(1, &sess->pasv_listen) ||
		!accept_socket(&sess->pasv_client, &sess->pasv_listen)) {
		close_socket(&sess->pasv_listen);
		return (false);
	}
	sess->netted = true;
	dprintf(1, "connected!\n");
	return (true);
}
