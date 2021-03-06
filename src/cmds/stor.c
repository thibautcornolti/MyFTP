/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"
#include "../../include/socket_tools.h"
#include "../../include/str_tools.h"

static void cmd_stor_do(sess_t *sess, char *file)
{
	int pid = fork();
	char buff[4096];
	int fd;
	size_t r = 0;

	if (pid > 0) {
		if ((fd = open(file, O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			exit(1);
		while ((r = read(sess->client.fd, buff, 4096)) != 0)
			write(fd, buff, r);
		exit(0);
	}
	else if (pid == 0)
		waitpid(pid, NULL, 0);
	else
		perror("Error when forking");
}

static void cmd_stor_lo(sess_t *sess, char *file, net_t *client)
{
	char *new;

	transform_file_path(sess, &file, &new);
	if (!new) {
		dprintf(client->fd, "550 Failed to open file.\n");
		return ;
	}
	if (!prepare_cmd(sess)) {
		dprintf(client->fd,
			"425 Unable to establish data connection.\n");
		return ;
	}
	dprintf(client->fd,
		"150 File status okay; about to open data connection.\n");
	cmd_stor_do(sess, new);
	finish_cmd(sess);
	dprintf(client->fd,
		"226 Closing data connection. Requested file action "
		"successful (for example, file transfer or file abort).\n");
}

bool cmd_stor(sess_t *sess, char *line, net_t *client)
{
	char *file = get_arg(line, 1);

	if (!sess->logged)
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
	else if (!sess->netted)
		dprintf(client->fd, "425 Use PORT or PASV first.\n");
	else
		cmd_stor_lo(sess, file, client);
	return (true);
}
