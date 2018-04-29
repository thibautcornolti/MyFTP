/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#pragma once

#include "client.h"
#include "passive.h"
#include "active.h"

bool prepare_cmd(sess_t *);
void finish_cmd(sess_t *);
