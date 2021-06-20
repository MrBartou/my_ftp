/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** loop
*/

#include "my.h"

void loop(server_t *server)
{
    struct sockaddr_in addr;

    while (1) {
        server->fd_client = accept(server->fd_serv,
            (struct sockaddr *)&addr, &server->socket);
        if(fork() == 0) {
            connection(server);
            break;
        }
    }
}