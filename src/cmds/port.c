/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/active.h"
#include "../../include/ftp.h"

static int get_port(char *addr)
{
	size_t port = 0;

	strtok(addr, ".");
	strtok(NULL, ".");
	strtok(NULL, ".");
	strtok(NULL, ".");
	port = atoi(strtok(NULL, ".")) * 256 + atoi(strtok(NULL, "."));
	free(addr);
	return (port);
}

static char *get_addr(char *addr)
{
	size_t dot = 0;

	for (size_t i = 0; i < strlen(addr); ++i) {
		if (addr[i] == '.')
			dot += 1;
		if (dot == 4) {
			addr[i] = 0;
			return (addr);
		}
	}
	return (addr);
}

bool cmd_port(sess_t *sess, char *line, net_t *client)
{
	char *addr = get_arg(line, 1);
	size_t port = 0;

	if (!sess->logged) {
		dprintf(client->fd, "530 Please login with USER and PASS.\n");
		return (true);
	}
	for (size_t i = 0; i < strlen(addr); ++i)
		if (addr[i] == ',')
			addr[i] = '.';
	port = get_port(strdup(addr));
	dprintf(1, "port=%ld\n", port);
	dprintf(client->fd, "200 PORT %s:%ld OK.\n", get_addr(addr), port);
	start_active_mode(sess, get_addr(addr), port);
	return (true);
}
