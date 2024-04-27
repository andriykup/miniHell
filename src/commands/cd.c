/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:55:05 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/27 16:55:07 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

char *com_cd(void)
{
    //adapt it to use com_pwd here !!!!
    char *pwd; 

    pwd = malloc(sizeof(char) * PATH_MAX);
    pwd = getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);

    chdir("/home/ankupins/");

    pwd = getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);


    free(pwd); //what if we need to return it???
    return (0);
}


int main()
{
    com_cd();
    return 0;
}
