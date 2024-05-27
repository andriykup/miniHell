#include "../../include/mini_hell.h"

int token_delimiter(char c)
{
    if (c == ' ')
        return (1);
    else if (c == '<')
        return (1);
    else if (c == '>')
        return (1);
    return (0);
}

void skip_space(char *input, int *i)
{
    while(input[(*i)] == ' ')
        i++;
}
