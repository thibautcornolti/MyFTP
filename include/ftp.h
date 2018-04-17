/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <linux/limits.h>
#include "../include/str_tools.h"
#include "../include/client.h"
#include "../include/socket.h"

bool commander(sess_t *, char *, net_t *);

bool cmd_user(sess_t *, char *, net_t *);
bool cmd_pass(sess_t *, char *, net_t *);
bool cmd_cwd(sess_t *, char *, net_t *);
bool cmd_cdup(sess_t *, char *, net_t *);
bool cmd_quit(sess_t *, char *, net_t *);
bool cmd_dele(sess_t *, char *, net_t *);
bool cmd_pwd(sess_t *, char *, net_t *);
bool cmd_pasv(sess_t *, char *, net_t *);
bool cmd_port(sess_t *, char *, net_t *);
bool cmd_help(sess_t *, char *, net_t *);
bool cmd_noop(sess_t *, char *, net_t *);
bool cmd_retr(sess_t *, char *, net_t *);
bool cmd_stor(sess_t *, char *, net_t *);
bool cmd_list(sess_t *, char *, net_t *);
bool cmd_auth(sess_t *, char *, net_t *);
bool cmd_type(sess_t *, char *, net_t *);
