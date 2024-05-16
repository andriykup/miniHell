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

// MEM LEAKS!!!!


char *com_cd(char *path)
{
    char *pwd; 

    pwd = malloc(sizeof(char) * PATH_MAX);
    pwd = getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);
    pwd = ft_strjoin(pwd, "/");
    pwd = ft_strjoin(pwd, path);
    printf("TEST = %s\n", pwd);
    chdir(pwd);

    pwd = getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);


    free(pwd);
    return (0);
}
