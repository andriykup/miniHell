/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:47:42 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/30 15:07:59 by aconvent         ###   ########.fr       */
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
