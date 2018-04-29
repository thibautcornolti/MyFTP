/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"
#include "../../include/socket_tools.h"
#include "../../include/str_tools.h"

static void cmd_retr_do(sess_t *sess, char *file)
{
	int pid = fork();
	char buff[4096];
	int fd;
	size_t r = 0;

	if (pid > 0) {
		if ((fd = open(file, O_RDONLY)) < 0)
			exit(1);
		while ((r = read(fd, buff, 4096)) != 0)
			write(sess->client.fd, buff, r);
		exit(0);
	} else if (pid == 0) {
		waitpid(pid, NULL, 0);
	} else
		perror("Error when forking");
}

static void cmd_retr_lo(sess_t *sess, char *file, net_t *client)
{
	char *new;
	struct stat st;

	transform_path(sess, &file, &new);
	if (!new || stat(new, &st) || !S_ISREG(st.st_mode) ||
		access(new, R_OK)) {
		dprintf(client->fd, "550 Failed to open file.\n");
		return ;
	}
	prepare_cmd(sess);
	dprintf(client->fd,
		"150 File status okay; about to open data connection.\n");
	cmd_retr_do(sess, new);
	finish_cmd(sess);
	dprintf(client->fd,
		"226 Closing data connection. Requested file action "
		"successful (for example, file transfer or file abort).\n");
}

bool cmd_retr(sess_t *sess, char *line, net_t *client)
{
	char *file = get_arg(line, 1);

	if (!sess->logged)
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
	else if (!sess->netted)
		dprintf(client->fd, "425 Use PORT or PASV first.\n");
	else
		cmd_retr_lo(sess, file, client);
	return (true);
}
