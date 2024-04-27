/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:47:42 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/27 14:47:43 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

char *com_pwd(void)
{
    char *pwd; 

    pwd = malloc(sizeof(char) * PATH_MAX);
    pwd = getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);

    free(pwd); //what if we need to return it???
    return (0);
}


// int main()
// {
//     com_pwd();
//     return 0;
// }