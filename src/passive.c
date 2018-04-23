/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/ftp.h"
#include "../include/passive.h"

static bool threading_passive_mode_setup(sess_t *sess)
{
	if (!create_socket(&sess->pasv_listen) ||
		!bind_socket(0, &sess->pasv_listen))
		return (false);
	if (!listen_socket(1, &sess->pasv_listen)) {
		close_socket(&sess->pasv_listen);
		return (false);
	}
	return (true);
}

static void *threading_passive_mode(void *d)
{
	sess_t *sess = d;

	if (!threading_passive_mode_setup(sess)) {
		pthread_cond_broadcast(&sess->pasv_cond);
		return (NULL);
	}
	getsockname(sess->pasv_listen.fd,
		(struct sockaddr *) &sess->pasv_listen.s_in,
		&sess->pasv_listen.s_in_len);
	sess->active = false;
	sess->netted = true;
	pthread_cond_broadcast(&sess->pasv_cond);
	pthread_mutex_lock(&sess->pasv_mutex);
	if (!accept_socket(&sess->client, &sess->pasv_listen)) {
		close_socket(&sess->pasv_listen);
		sess->netted = false;
		pthread_mutex_unlock(&sess->pasv_mutex);
	} else
		pthread_mutex_unlock(&sess->pasv_mutex);
	return (NULL);
}

void start_passive_mode(sess_t *sess)
{
	kill_passive_mode(sess);
	pthread_create(&sess->pasv_thread, NULL, &threading_passive_mode, sess);
	pthread_cond_wait(&sess->pasv_cond, &sess->pasv_cond_mutex);
	usleep(10000);
}

void kill_passive_mode(sess_t *sess)
{
	struct sockaddr_in temp_sock = {0};
	struct hostent *server = gethostbyname("0");
	struct protoent *proto = getprotobyname("TCP");
	int fd;

	if (!proto)
		return ;
	if ((fd = socket(AF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return ;
	temp_sock.sin_family = AF_INET;
	temp_sock.sin_port = sess->pasv_listen.s_in.sin_port;
	memcpy(server->h_addr, &temp_sock.sin_addr.s_addr, server->h_length);
	if (connect(fd, (struct sockaddr *) &temp_sock, sizeof(temp_sock)))
		return ;
	close_passive_mode(sess);
	close(fd);
}

void close_passive_mode(sess_t *sess)
{
	sess->netted = false;
	sess->active = false;
	close_socket(&sess->pasv_listen);
	close_socket(&sess->client);
}
