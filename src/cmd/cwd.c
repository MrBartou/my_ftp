/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** cwd
*/

#include "my.h"

void cwd(char **commands, client_t *client)
{
    if (commands[1] && chdir(commands[1]) != 1) {
        dprintf(client->fd, "250 Requested file action okay, completed.\t\n");
    }
}