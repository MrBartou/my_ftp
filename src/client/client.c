/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** client
*/

#include "my.h"

client_t *create_client(server_t *server)
{
    client_t *new_client = malloc(sizeof(*new_client));

    new_client->user = NULL;
    new_client->fd = server->fd_client;
    new_client->password = 0;
    return (new_client);
}

void connection(server_t *server)
{
    char *line = NULL;
    client_t *client = create_client(server);
    FILE *fd = fdopen(server->fd_client, "r");
    size_t len = 100;
    char **commands = NULL;

    dprintf(server->fd_client, "220 Service ready for new user.\n");
    while (getline(&line, &len, fd) != EOF) {
        commands = my_str_to_word_array(line);
        found_command(commands, client);
    }
}