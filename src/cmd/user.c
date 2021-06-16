/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** user
*/

#include "my.h"

void user(char **commands, client_t *client)
{
    client->user = strdup(commands[1]);
    dprintf(client->fd, "331 User name okay, need password.\t\n");
}