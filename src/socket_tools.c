/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/socket_tools.h"

void prepare_cmd(sess_t *sess)
{
	if (!sess->active)
		pthread_mutex_lock(&sess->pasv_mutex);
}

void finish_cmd(sess_t *sess)
{
	if (sess->active)
		close_active_mode(sess);
	else {
		close_passive_mode(sess);
		pthread_mutex_unlock(&sess->pasv_mutex);
	}
}