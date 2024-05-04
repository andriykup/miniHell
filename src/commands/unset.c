/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:00:54 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/28 12:00:57 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"


static void free_node(t_env *node)
{
    free(node->key);
    free(node->value);
    free(node);
}

int com_unset(t_env **head, char *env)
{
    t_env *node;

    node = find_env_var(*head, env);
    // remove an environment variable so that it's no longer accessible, use unset with the variable name.
    // unset MY_VAR  # Removes MY_VAR from the environment

    if(node == NULL)
    {
        printf("env var doesnt exist!\n");
        return (-1);
    }

    if(node->prev != NULL)
        node->prev->next = node->next;
    else
        head = &node->next;
    if(node->next != NULL)
        node->next->prev = node->prev;
    free_node(node);
    return (0);
}
