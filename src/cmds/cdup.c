/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../../include/ftp.h"

bool cmd_cdup(sess_t *sess, char *line, net_t *client)
{
	(void) line;
	return (cmd_cwd(sess, "cwd ..\n", client));
}
