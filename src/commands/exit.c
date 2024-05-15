/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:03:44 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/28 12:03:45 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

void com_exit(t_mini_shell mini_shell, t_env *my_env)
{
    free_struct(mini_shell);
    free_my_env(my_env);
	exit (0);
}
