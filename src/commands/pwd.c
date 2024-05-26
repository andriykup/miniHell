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

    pwd = getcwd(NULL, 0);
    if(pwd == NULL)
        return NULL;
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}
