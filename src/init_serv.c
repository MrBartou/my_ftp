/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** init_serv
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
            printf("--- Client disconnected: %s\n", tmp);
            close(server->fd_client);
        }
    }
}

void init_serv(char **av)
{
    server_t *server = malloc(sizeof(*server));

    server->proto = getprotobyname("TCP");
    server->path = av[2];
    server->port = atoi(av[1]);
    server->fd_serv = socket(AF_INET, SOCK_STREAM, server->proto->p_proto);
    server->socket = sizeof(server->socket_in);
    server->socket_in.sin_family = AF_INET;
    server->socket_in.sin_port = htons(server->port);
    server->socket_in.sin_addr.s_addr = INADDR_ANY;
    bind(server->fd_serv, (const struct sockaddr *)&server->socket_in,
        sizeof(server->socket_in));
    listen(server->fd_serv, 50);
    printf("%s", "\nServer is connect on 127.0.0.1\n");
    loop(server);
    shutdown(server->fd_serv, SHUT_WR);
}