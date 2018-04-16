/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/socket.h"
#include "../include/client.h"

static void fork_client(net_t *client)
{
	char buff[2048];
	size_t r;

	while (1) {
		r = read(client->fd, buff, 2048);
		buff[r] = 0;
		dprintf(client->fd, "%s", buff);
	}
}

bool accept_clients(net_t *server)
{
	while (20) {
		net_t client = {0};
		if (!accept_socket(&client, server))
			continue ;
		if (fork()) {
			printf("Client %s connected!\n",
				inet_ntoa(client.s_in.sin_addr));
			close_socket(&client);
		} else {
			close_socket(server);
			fork_client(&client);
		}
	}
	return (true);
}
