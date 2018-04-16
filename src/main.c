/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/socket.h"
#include "../include/client.h"
#include "../include/myftp.h"

int main(void)
{
	net_t srv = {0};

	if (!create_socket(&srv) || !bind_socket(4000, &srv))
		return (84);
	if (!listen_socket(1024, &srv) || !accept_clients(&srv)) {
		close_socket(&srv);
		return (84);
	}
	close_socket(&srv);
	return (0);
}
