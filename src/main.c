/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include <linux/limits.h>
#include <stdlib.h>
#include "../include/socket.h"
#include "../include/client.h"

static char *get_path(char *old)
{
	char *res = malloc(PATH_MAX);

	realpath(old, res);
	return (res);
}

int main(int ac, char **av)
{
	net_t srv = {0};
	int port;
	char *anonymousPath;

	if (ac != 3)
		return (84);
	if ((port = atoi(av[1])) == 0)
		return (84);
	anonymousPath = get_path(av[2]);
	if (!create_socket(&srv) || !bind_socket(port, &srv))
		return (84);
	if (!listen_socket(1024, &srv) || !accept_clients(anonymousPath, &srv)) {
		close_socket(&srv);
		return (84);
	}
	close_socket(&srv);
	return (0);
}
