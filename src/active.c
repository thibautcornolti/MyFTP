/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/active.h"
#include "../include/ftp.h"

bool start_active_mode(sess_t *sess, char *ip, int port)
{
	struct hostent *server = gethostbyname(ip);

	create_socket(&sess->client);
	sess->client.s_in.sin_family = AF_INET;
	memcpy(server->h_addr, &sess->client.s_in.sin_addr.s_addr,
		server->h_length);
	sess->client.s_in.sin_port = htons(port);
	sess->active = true;
	sess->netted = true;
	return (true);
}

bool connect_active_mode(sess_t *sess)
{
	int ret = 1;

	for (size_t i = 0 ; i < 20 && ret ; ++i) {
		ret = connect(sess->client.fd,
			(struct sockaddr *)&sess->client.s_in,
			sizeof(sess->client.s_in));
		if (ret)
			sleep(1);
	}
	return (ret == 0);
}

void close_active_mode(sess_t *sess)
{
	sess->active = false;
	sess->netted = false;
	close_socket(&sess->client);
}
