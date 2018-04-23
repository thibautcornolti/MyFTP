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

bool start_active_mode(sess_t *, char *, int);
void close_active_mode(sess_t *);
