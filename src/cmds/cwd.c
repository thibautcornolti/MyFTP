/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"
#include "../../include/str_tools.h"

static void do_cwd(sess_t *sess, char *path, net_t *client)
{
	char *new;
	DIR *dir;

	transform_path(sess, &path, &new);
	if (new && strstr(new, sess->home) != new)
		dprintf(client->fd,
			"250 Requested file action okay, completed.\n");
	else if (new && (dir = opendir(new))) {
		free(sess->pathname);
		sess->pathname = new;
		closedir(dir);
		dprintf(client->fd,
			"250 Requested file action okay, completed.\n");
	}
	else
		dprintf(client->fd, "550 Failed to change directory.\n");
	free(path);
}

bool cmd_cwd(sess_t *sess, char *line, net_t *client)
{
	char *path = get_arg(line, 1);

	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	if (!path) {
		dprintf(client->fd, "550 Failed to change directory.\n");
		return (true);
	}
	do_cwd(sess, path, client);
	return (true);
}
