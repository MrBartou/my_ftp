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

    // POINTER
    static const char *function[8] = {
        "HELP",
        "USER",
        "PASS",
        "QUIT",
        "CDUP",
        "CWD",
        "PWD",
        NULL
    };

    // STRUCT
    typedef struct client_s {
        int fd;
        char *user;
        int password;
    } client_t;
    typedef struct server_s {
        int fd_serv;
        int fd_client;
        struct protoent *proto;
        struct sockaddr_in socket_in;
        socklen_t socket;
    } server_t;

    // CMD
    void cwd(char **commands, client_t *client);
    void help(char **commands, client_t *client);
    void pass(char **commands, client_t *client);
    void pwd(char **commands, client_t *client);
    void quit(char **commands, client_t *client);
    void user(char **commands, client_t *client);
    void cdup(char **commands, client_t *client);

    // HELP
    void helper();

    //INIT SERVER
    void init_serv(char **av);
    void loop(server_t *server);

    // CLIENT
    void connection(server_t *server);
    void found_command(char **commands, client_t *client);

    // lIB
    char **my_str_to_word_array(char *str);
    char *get_next_line(int fd);

#endif /* !MY_H_ */