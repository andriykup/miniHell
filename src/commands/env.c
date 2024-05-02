/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 12:02:52 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/28 12:02:54 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

void com_env(t_env *head)
{
    t_env *current = head;

    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
