/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** check_command
*/

#include "my.h"

void found_command(char **commands, client_t *client)
{
    for (int i = 0; function[i] != NULL; i++) {
        if (strcasecmp(commands[0], function[i]) == 0) {
            void (*function[10])(char **commands, client_t *client) =
            {&help, &user, &pass, &quit, &cdup, &cwd, &pwd};
            (*function[i])(commands, client);
        }
    }
    return;
}