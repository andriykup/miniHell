#include "../../include/mini_hell.h"


void skip_space(char *input, int *i)
{
    while(input[(*i)] == ' ')
        i++;
}
