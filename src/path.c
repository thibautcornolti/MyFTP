/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/ftp.h"

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

static void write_slash(sess_t *sess, char **path)
{
	char *new = malloc(strlen(*path) + PATH_MAX);

	memset(new, 0, strlen(*path) + PATH_MAX);
	strcpy(new, sess->home);
	strcat(new, "/");
	strcat(new, *path);
	free(*path);
	*path = new;
}

void transform_path(sess_t *sess, char **path, char **new)
{
	if ((*path)[0] == '~')
		write_tilt(sess, path);
	else if ((*path)[0] != '/')
		write_dot(sess, path);
	else
		write_slash(sess, path);
	*new = realpath(*path, 0);
}

void transform_file_path(sess_t *sess, char **path, char **new)
{
	char *filename;
	size_t last_slash = 0;

	for (size_t i = 0; i < strlen(*path); ++i)
		if ((*path)[i] == '/')
			last_slash = i;
	filename = strdup((*path) + last_slash);
	(*path)[last_slash] = 0;
	transform_path(sess, path, new);
	if (*new) {
		strcat(*new, "/");
		strcat(*new, filename);
	}
}
