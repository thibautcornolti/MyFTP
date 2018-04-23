/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_dele(sess_t *sess, char *line, net_t *client)
{
	char *path = get_arg(line, 1);
	char *new;

	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	transform_file_path(sess, &path, &new);
	if (!remove(new))
		dprintf(client->fd, "250 Requested file action okay, \
completed.\n");
	else
		dprintf(client->fd, "550 Failed to remove file.\n");
	free(new);
	return (true);
}
