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
    char *tmp = calloc(INET_ADDRSTRLEN, sizeof(*tmp));

    while (1) {
        server->fd_client = accept(server->fd_serv,
            (struct sockaddr *)&addr, &server->socket);
        if(fork() == 0) {
            inet_ntop(AF_INET, (struct in_addr *)&addr.sin_addr, tmp, INET_ADDRSTRLEN);
            printf("--- New client: %s\n", tmp);
            connection(server);
            break;
        }
    }
}