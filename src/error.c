/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:59:25 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 17:59:29 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_hell.h"

//              error codes:
// -1 - 
// -2 -
// -3 - 
// -4 - 

void error(int error_code, t_mini_shell mini_shell)
{
    if(error_code == -1)
    {
        printf("Error: command not found\n");
        free_struct(mini_shell);
        exit(EXIT_FAILURE);
    }
    else if(error_code == -2)
    {
        printf("Error: invalid arguments\n");
        free_struct(mini_shell);
        exit(EXIT_FAILURE);
    }
}