/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** pass
*/

#include "my.h"

void pass(char **commands, client_t *client)
{
    (void)commands;
    if (client->password == 1)
        dprintf(client->fd, "230 User logged in, proceed.\r\n");
    else {
        client->password = 1;
        dprintf(client->fd, "230 User logged in, proceed.\r\n");
    }
}