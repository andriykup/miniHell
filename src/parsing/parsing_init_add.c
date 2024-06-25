/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:33:11 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/25 12:51:44 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

t_redir *redir_init()
{
    t_redir *new_redir;
    new_redir = malloc(sizeof(t_redir));
    if (new_redir == NULL) {
        // error management
        return NULL;
    }
    new_redir->file_name = NULL;
    new_redir->delimiter = NULL;
    new_redir->redir = NULL;
    new_redir->next = NULL;
    return new_redir;
}

t_command* init_command()
{
    t_command *new_command;
    new_command = (t_command*)malloc(sizeof(t_command));
    if (new_command == NULL) 
    {
        return NULL;
    }
    new_command->args = NULL;
    new_command->redir = NULL;
    new_command->redirected = false;
    new_command->next = NULL;
    return new_command;
}

void add_command_to_end(t_command **head, t_command *new_node)
{
    t_command *current;

    if (head == NULL || new_node == NULL)
        return;
    if (!*head )
    {
        *head = new_node;
    }
    else 
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void add_redir_to_end(t_redir **head, t_redir *new_node)
{
    t_redir *current;
    if (head == NULL || new_node == NULL)
        return;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current = *head;
        while (current->next != NULL) 
            current = current->next;
        current->next = new_node;
    }
}
