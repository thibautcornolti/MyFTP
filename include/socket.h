/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

typedef struct {
	struct sockaddr_in s_in;
	socklen_t s_in_len;
	struct protoent *protocol_ent;
	int fd;
} net_t;

bool create_socket(net_t *);
bool bind_socket(int, net_t *);
bool listen_socket(int, net_t *);
bool accept_socket(net_t *, net_t *);
bool close_socket(net_t *);
