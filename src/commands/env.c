/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:02:52 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/14 14:46:04 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

void com_env(char**command, t_env *head)
{
    if (command[1] != NULL)
    {
        printf("env: %s: No such file or directory\n",command[1]);
        return;
    }
    t_env *current = head;

    while (current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
