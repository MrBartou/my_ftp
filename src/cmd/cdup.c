/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** cdup
*/

#include "my.h"

void cdup(char **commands, client_t *client)
{
    (void)commands;

    if (chdir("../") != -1) {
        dprintf(client->fd, "200 Command okay.\n\t");
    }
}