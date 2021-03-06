/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/client.h"
#include "../include/active.h"
#include "../include/ftp.h"
#include "../include/passive.h"
#include "../include/socket.h"

static void loop_client(sess_t *sess, net_t *client)
{
	char buff[2049];
	char c;
	size_t idx;
	int ret;

	do {
		c = 0;
		idx = 0;
		memset(buff, 0, 2049);
		while (c != '\n' && c != '\r' &&
			(ret = read(client->fd, &c, 1))) {
			if (c)
				buff[idx++ % 2048] = c;
		}
	} while (ret > 0 && commander(sess, buff, client));
}

static void fork_client(char *anonymousPath, net_t *client)
{
	sess_t session = {0};

	session.pathname = strdup(anonymousPath);
	session.home = strdup(anonymousPath);
	pthread_mutex_init(&session.pasv_mutex, NULL);
	dprintf(client->fd, "220 Service ready for new user.\n");
	loop_client(&session, client);
	if (session.netted && session.active)
		close_active_mode(&session);
	else if (session.netted)
		close_passive_mode(&session);
	dprintf(1, "Client %s disconnected!\n",
		inet_ntoa(client->s_in.sin_addr));
	close_socket(client);
	exit(0);
}

bool accept_clients(char *anonymousPath, net_t *server)
{
	dprintf(1, "Server started on %d!\n", ntohs(server->s_in.sin_port));
	while (20) {
		net_t client = {0};
		if (!accept_socket(&client, server))
			continue;
		if (fork()) {
			dprintf(1, "Client %s connected!\n",
				inet_ntoa(client.s_in.sin_addr));
			close_socket(&client);
		}
		else
			fork_client(anonymousPath, &client);
	}
	return (true);
}
