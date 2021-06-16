/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** pwd
*/

#include "my.h"

void pwd(char **commands, client_t *client)
{
    (void)commands;
    char *path = NULL;

    path = malloc(sizeof(*path) * 300);
    path = getcwd(path, 300);
    dprintf(client->fd, "257 \"%s\" created.\t\n", path);
    free(path);
}