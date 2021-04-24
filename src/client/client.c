/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** client
*/


#include "my.h"

void connection(server_t *server)
{
    dprintf(server->fd_client, "220 Connected to myftp\n");
}