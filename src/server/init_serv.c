/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** init_serv
*/

#include "my.h"

server_t *init_struct(server_t *server, char **av)
{
    server->proto = getprotobyname("TCP");
    server->fd_serv = socket(AF_INET, SOCK_STREAM, server->proto->p_proto);
    server->socket = sizeof(server->socket_in);
    server->socket_in.sin_family = AF_INET;
    server->socket_in.sin_port = htons(atoi(av[1]));
    server->socket_in.sin_addr.s_addr = INADDR_ANY;
    return (server);
}

void init_serv(char **av)
{
    server_t *server = malloc(sizeof(*server));

    server = init_struct(server, av);
    printf("%s", "\nServer is connect on 127.0.0.1\n");
    bind(server->fd_serv, (const struct sockaddr *)&server->socket_in,
        sizeof(server->socket_in));
    loop(server);
}