/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include <pthread.h>
#include "../include/client.h"
#include "../include/socket.h"

typedef struct {
	net_t *client;
	sess_t *session;
	pthread_mutex_t mutex;
} thread_passive_data_t;

void start_passive_mode(sess_t *);
void kill_passive_mode(sess_t *);
void close_passive_mode(sess_t *);
