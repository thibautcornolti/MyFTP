/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"
#include "../../include/active.h"
#include "../../include/passive.h"
#include "../../include/socket_tools.h"

static void cmd_list_do(sess_t *sess, char *path)
{
	char *cmd;
	int pid = fork();

	if (pid > 0) {
		asprintf(&cmd, "ls -l %s | tail -n+2", path);
		dup2(sess->client.fd, 1);
		dup2(sess->client.fd, 2);
		system(cmd);
		exit(0);
	}
	else if (pid == 0) {
		waitpid(pid, NULL, 0);
	}
	else {
		perror("Error when forking");
	}
}

static char *is_good_path(sess_t *sess, char *path, net_t *client)
{
	char *new = NULL;

	transform_path(sess, &path, &new);
	if (!new || opendir(new) == NULL) {
		dprintf(client->fd, "550 Permission denied.\n");
		return (NULL);
	}
	return (new);
}

static void cmd_list_lo(sess_t *sess, char *arg, net_t *client)
{
	if (!arg)
		arg = sess->pathname;
	else if (!(arg = is_good_path(sess, arg, client)))
		return ;
	if (!prepare_cmd(sess)) {
		dprintf(client->fd,
			"425 Unable to establish data connection.\n");
		return ;
	}
	dprintf(client->fd,
		"150 File status okay; about to open data connection.\n");
	cmd_list_do(sess, arg);
	finish_cmd(sess);
	dprintf(client->fd,
		"226 Closing data connection. Requested file action "
		"successful (for example, file transfer or file abort).\n");
}

bool cmd_list(sess_t *sess, char *line, net_t *client)
{
	char *arg = get_arg(line, 1);

	if (!sess->logged)
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
	else if (!sess->netted)
		dprintf(client->fd, "425 Use PORT or PASV first.\n");
	else
		cmd_list_lo(sess, arg, client);
	return (true);
}
