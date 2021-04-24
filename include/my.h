/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <arpa/inet.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/types.h>

    // STRUCT
    typedef struct server_s {
        int fd_serv;
        int fd_client;
        int port;
        char *path;
        struct protoent *proto;
        struct sockaddr_in socket_in;
        socklen_t socket;
    } server_t;

    // HELP
    void helper();

    //INIT SERVER
    void init_serv(char **av);
    void loop(server_t *server);

    // CLIENT
    void connection(server_t *server);

#endif /* !MY_H_ */