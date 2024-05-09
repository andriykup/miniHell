/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/05/09 12:51:36 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

typedef struct s_commands
{
    char *cmd;
    char *flags;
    char *input;
    t_simp_cmd *next;
}t_simp_cmd;


/*
    how to handle multiples flags separated by a space ?????
*/

t_simp_cmd *spliting(t_mini_shell *mini)
{
    int i;
    t_simp_cmd *cmds;
    
    
    
    
}
