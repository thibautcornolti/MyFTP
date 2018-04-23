/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "../include/socket.h"

typedef struct {
	char *user;
	bool logged;
	char *pathname;
	char *home;
	net_t pasv_listen;
	net_t pasv_client;
	pthread_t pasv_thread;
	pthread_mutex_t pasv_mutex;
	pthread_mutex_t pasv_cond_mutex;
	pthread_cond_t pasv_cond;
	bool netted;
	bool netting;
} sess_t;

bool accept_clients(char *, net_t *);
