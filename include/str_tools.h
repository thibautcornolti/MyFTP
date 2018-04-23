/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

char *to_upper_case(char *);
char *get_arg(char *, int);
void transform_path(sess_t *, char **, char **);
void transform_file_path(sess_t *, char **, char **);
