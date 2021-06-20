/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** help
*/

#include "my.h"

void help(char **commands, client_t *client)
{
    (void)commands;
    (void)client;
    dprintf(client->fd, "214 Help message:\
    \n\tUSER\n\tPASS\n\tQUIT\n\tHELP\n\tCDUP\n\tCWD\t\nPWD\t\n");
}