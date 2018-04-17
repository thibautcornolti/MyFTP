/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

static void write_tilt(sess_t *sess, char **path)
{
	char *new = malloc(strlen(*path) + PATH_MAX);

	memset(new, 0, strlen(*path) + PATH_MAX);
	strcpy(new, sess->home);
	strcat(new, "/");
	strcat(new, (*path) + 1);
	free(*path);
	*path = new;
}

static void write_dot(sess_t *sess, char **path)
{
	char *new = malloc(strlen(*path) + PATH_MAX);

	memset(new, 0, strlen(*path) + PATH_MAX);
	strcpy(new, sess->pathname);
	strcat(new, "/");
	strcat(new, *path);
	free(*path);
	*path = new;
}

bool cmd_cwd(sess_t *sess, char *line, net_t *client)
{
	char *path = get_arg(line, 1);
	char *new;
	DIR *dir;

	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	if (path[0] == '~')
		write_tilt(sess, &path);
	else if (path[0] != '/')
		write_dot(sess, &path);
	new = realpath(path, 0);
	dprintf(1, "%s\n", new);
	if (new && (dir = opendir(new))) {
		free(sess->pathname);
		sess->pathname = new;
		dprintf(client->fd, "250 Requested file action okay, \
completed.\n");
		closedir(dir);
	} else {
		dprintf(client->fd, "550 Failed to change directory.\n");
	}
	free(path);
	return (true);
}
