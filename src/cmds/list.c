/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"
#include "../../include/passive.h"
#include "../../include/active.h"

static void cmd_list_do(sess_t *sess)
{
	char *cmd;
	int pid = fork();

	if (pid > 0) {
		asprintf(&cmd, "ls -l %s", sess->pathname);
		dup2(sess->client.fd, 1);
		dup2(sess->client.fd, 2);
		system(cmd);
		exit(0);
	} else if (pid == 0) {
		waitpid(pid, NULL, 0);
	} else {
		perror("Error when forking");
	}
}

static void prepare(sess_t *sess)
{
	if (!sess->active)
		pthread_mutex_lock(&sess->pasv_mutex);
}

static void finish(sess_t *sess)
{
	if (sess->active)
		close_active_mode(sess);
	else {
		close_passive_mode(sess);
		pthread_mutex_unlock(&sess->pasv_mutex);
	}
}

bool cmd_list(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	if (!sess->logged)
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
	else if (!sess->netted)
		dprintf(client->fd, "425 Use PORT or PASV first.\n");
	else {
		prepare(sess);
		dprintf(client->fd, "150 File status okay; about to open data \
connection.\n");
		cmd_list_do(sess);
		finish(sess);
		dprintf(client->fd, "226 Closing data connection. Requested \
file action successful (for example, file transfer or file abort).\n");
	}
	return (true);
}
