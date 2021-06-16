/*
** EPITECH PROJECT, 2021
** my_ftp
** File description:
** my_str_to_word_array
*/

#include "my.h"

int is_charac(char c, int status)
{
    if (status == 1)
        if (c >= 33 && c <= 126)
            return EXIT_FAILURE;
    if (status == 2)
        if (c >= 33 && c <= 126 && c != 58)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int coumpt(char *str)
{
    int	count = 0;

    for (int a = 0; str[a] != '\0'; a++)
        if (is_charac(str[a], 1) == 1 && is_charac(str[a + 1], 1) != 1)
            count++;
    return (count);
}

int len_of_word(char *str, int i)
{
    for (; str[i] != '\0'; i++)
        if (is_charac(str[i], 1) != 1)
            break;
    return (i);
}

char **my_str_to_word_array(char *str)
{
    int	y = coumpt(str);
    char **result = NULL;

    result = malloc(sizeof(char *) * y + 1);
    if (result == NULL)
        return NULL;
    for (int a = 0, b = 0, c = 0; b < y; a++, b++) {
        c = 0;
        result[b] = malloc(sizeof(char) * len_of_word(str, a));
        if (result == NULL)
            return NULL;
        for (; str[a] == ' ' || str[a] == '\t'; a++);
        for (; str[a] != '\0' && is_charac(str[a], 1) == 1; a++, c++)
            result[b][c] = str[a];
        result[b][c] = '\0';
    }
    result[y] = NULL;
    return (result);
}

char **str_to_commat(char *str, char pivot)
{
    int	y = strlen(str);
    char **result = NULL;

    result = malloc(sizeof(char *) * y + 1);
    if (result == NULL)
        return NULL;
    for (int count = 0; count <= y ; count++)
        result[count] = NULL;
    for (int a = 0, b = 0, c = 0; b < y; a++, b++) {
        c = 0;
        result[b] = malloc(sizeof(char) * y);
        if (result == NULL)
            return NULL;
        for (; str[a] != '\0' && str[a] != pivot ; a++, c++)
            result[b][c] = str[a];
        result[b][c] = '\0';
    }
    return (result);
}