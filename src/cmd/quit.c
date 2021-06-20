/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** quit
*/

#include "my.h"

void quit(char **commands, client_t *client)
{
    (void)commands;
    dprintf(client->fd, "221 Service closing control connection.\r\n");
    close(client->fd);
}