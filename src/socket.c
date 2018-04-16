/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/socket.h"

bool create_socket(net_t *ns)
{
	if ((ns->protocol_ent = getprotobyname("TCP")) == NULL)
		return (false);
	ns->fd = socket(AF_INET, SOCK_STREAM, ns->protocol_ent->p_proto);
	if (ns->fd == -1) {
		perror("Error when creating socket");
		return (false);
	}
	if (setsockopt(ns->fd, SOL_SOCKET, SO_REUSEADDR,
		&(int){ 1 }, sizeof(int)) < 0)
    		return (false);
	return (true);
}

bool bind_socket(int port, net_t *ns)
{
	ns->s_in.sin_family = AF_INET;
	ns->s_in.sin_port = htons(port);
	ns->s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind(ns->fd, (const struct sockaddr *) &ns->s_in,
		sizeof(ns->s_in)) == -1) {
		perror("Error when binding socket");
		return (false);
	}
	return (true);
}

bool listen_socket(int nb, net_t *ns)
{
	if (listen(ns->fd, nb) == -1) {
		perror("Error when listening socket");
		return (false);
	}
	return (true);
}

bool accept_socket(net_t *nc, net_t *ns)
{
	nc->s_in_len = sizeof(nc->s_in);
	if ((nc->fd = accept(ns->fd,
		(struct sockaddr *) &nc->s_in, &nc->s_in_len)) == -1) {
		perror("Error when accepting socket");
		return (false);
	}
	return (true);
}

bool close_socket(net_t *n)
{
	if (n->fd >= 0)
		close(n->fd);
	return (true);
}
