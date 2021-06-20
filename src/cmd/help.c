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
    \r\nUSER\r\nPASS\r\nQUIT\r\nHELP\r\nCDUP\r\nCWD\r\nPWD\r\n");
}