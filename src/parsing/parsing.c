/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/16 16:00:56 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"



//dequoting file name but not redir in t_redir 


char   *command_quotes(char *str, t_env *env)
{
    int i;
    bool quotes;
    bool dquotes;
    
    quotes = true;
    dquotes = true;
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\'' && dquotes == true)
        {
            quotes = !quotes;
            quotes_out(&str[i], &str[i + 1]);
        }
        else if (str[i] == '"' && quotes == true)
        {
            dquotes = !dquotes;
            dquotes_work(str, env);
            quotes_out(&str[i], &str[i + 1]);
        }
    }
    if (!quotes || !dquotes)
    {
        return (ft_strdup(""));
    }
    str[i] = '\0';
    return (ft_strdup(str));
}


t_command *command_list(t_mini_shell *mini_shell)
{
    t_command *cmd_head;
    t_command *cmd;
    int i = 0;

    cmd_head = NULL;
    while (mini_shell->parsed_input[i] != NULL) 
    {
        cmd = init_command();
        if (cmd == NULL)
            return NULL;
        get_command(mini_shell->parsed_input[i], &cmd);
        add_command_to_end(&cmd_head, cmd);
        i++;
    }
    return cmd_head;
}


void parse_quotes_args(t_mini_shell **mini_shell, t_env *env)
{
    t_command *current_cmd ;
    char *processed_arg;
    int i;
    
    current_cmd = (*mini_shell)->commands;
    while (current_cmd) 
    {
        i = 0;
        while (current_cmd->args && current_cmd->args[i]) 
        {
            processed_arg = ft_strdup(command_quotes(current_cmd->args[i], env));
            if (processed_arg) 
            {
                free(current_cmd->args[i]);
                current_cmd->args[i] = NULL;
                current_cmd->args[i] = ft_strdup(processed_arg);
                free(processed_arg);
            }
            i++;
        }
        current_cmd = current_cmd->next;
    }
}

