/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:55:05 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/14 20:53:48 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

// need to work for directing to the correct dirrector


static char *st_strjoin(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    if (result == NULL) 
        return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

// MEM LEAKS!!!!
char *com_cd(char *path)
{
    char *pwd;
    char *new_path;
    char *full_path;

    pwd = getcwd(NULL, 0);
    //pwd = malloc(sizeof(char) * PATH_MAX);
    
    new_path = st_strjoin(pwd, "/");
    if(new_path == NULL)
    {
        free(pwd);
        return NULL;
    }
    full_path = st_strjoin(new_path, path);
    if(full_path == NULL)
    {
        free(pwd);
        free(new_path);
        return NULL;
    }
    free(new_path);
    chdir(full_path);

    free(pwd);
    free(full_path);
    return (0); //do we need to return new working directory??
}
