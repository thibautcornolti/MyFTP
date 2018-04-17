/*
** EPITECH PROJECT, 2018
** myftp
** File description:
** myftp
*/

#include "../include/str_tools.h"

char *to_upper_case(char *str)
{
	for (size_t i = 0 ; str[i] ; ++i)
		str[i] = toupper(str[i]);
	return (str);
}

char *get_arg(char *line, int nb)
{
	size_t temp = 0;

	for (size_t i = 0 ; line[i] ; ++i) {
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r') {
			nb -= 1;
			temp = (nb < 0) ? temp : i + 1;
		}
		if (nb < 0)
			return (strndup(line + temp, i - temp));
	}
	return (strdup(line));
}
