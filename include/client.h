/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include "../include/socket.h"

typedef struct {
	char *user;
	bool logged;
	char *pathname;
	char *home;
	net_t pasv_listen;
	net_t pasv_client;
	bool netted;
} sess_t;

bool accept_clients(char *, net_t *);
