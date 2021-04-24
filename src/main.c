/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** main
*/

#include "my.h"

int main(int ac, char **av)
{
    if (ac != 3) {
        if (ac == 2 && strcmp(av[1], "-help") == 0) {
            helper();
            return(EXIT_SUCCESS);
        }
        printf("Error with arguments");
        return (84);
    } else
        init_serv(av);
}