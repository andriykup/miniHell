/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:47:42 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/13 18:54:31 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

char *com_pwd(char **command)
{
    char *pwd;
    
    /*
        checking if there is anything else beside the function name
        example 
        pwd --->is correct 
        pwd (some chars) --> pwd: too many argument
        so by passing command we can check if (command[1] is NULL)
    */
    if (command[1] != NULL)
    {
        //error management
        printf("pwd: too many argument\n");
        return (0);
    }
    //pwd = malloc(sizeof(char) * PATH_MAX);
    pwd = getcwd(NULL, 0);
    if(pwd == NULL)
        return NULL;
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}


// int main()
// {
//     com_pwd();
//     return 0;
// }