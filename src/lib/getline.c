/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** getline
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *get_next_line(int fd)
{
    char save_cmd[5] = {'\0'};
    int len = 1;
    int readed = 1;
    int cmp = 0;
    char *res = NULL;

    res = malloc(sizeof(*res) * 100);
    for (;readed != 0 && save_cmd[len] != '\n';) {
        if (readed <= len) {
            readed = read(fd, save_cmd, 4);
            len = 0;
        }
        for (;readed > len && save_cmd[len] != '\n';
            res[cmp++] = save_cmd[len++]);
    }
    return (res);
}