/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:03:44 by ankupins          #+#    #+#             */
/*   Updated: 2024/06/05 14:00:09 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

void com_exit(t_mini_shell mini_shell, t_env *my_env)
{
    //free_struct(mini_shell);
    free_my_env(my_env);
    free(mini_shell.my_paths);
    
    //free(mini_shell.commands->args);
	exit (0);
}
