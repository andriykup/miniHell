/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/25 12:51:54 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"



//dequoting file name but not redir in t_redir 


char   *command_quotes(char *str, t_env *env)
{
    int quotation;
    int i;
    bool quotes;
    bool dquotes;
    
    quotation = 0;
    quotes = true;
    dquotes = true;
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\'' && dquotes == true)
        {
            quotation = 1;
            quotes = !quotes;
            quotes_out(&str[i], &str[i + 1]);
        }
        else if (str[i] == '"' && quotes == true)
        {
            quotation = 1;
            dquotes = !dquotes;
            quotes_out(&str[i], &str[i + 1]);
            dquotes_work(str, env);
        }
    }
    if ( quotation == 0)
     dquotes_work(str, env);
    if (!quotes || !dquotes)
        return (ft_strdup(""));
    return (ft_strdup(str));
}


t_command *command_list(t_mini_shell *mini_shell, t_env *env)
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
        get_command(mini_shell->parsed_input[i], &cmd, env);
        add_command_to_end(&cmd_head, cmd);
        i++;
    }
    return cmd_head;
}

void parse_quotes_args(t_command *current_cmd, t_env *env)
{
    char *processed_arg;
    int i;
    
    while (current_cmd != NULL) 
    {
        i = -1;
        while (current_cmd->args[++i] != NULL) 
        {
            processed_arg = command_quotes(current_cmd->args[i], env);
            if (processed_arg) 
            {
               current_cmd->args[i] = ft_strdup(processed_arg);
                free(processed_arg);
                processed_arg = NULL;
            }
        }
        if (current_cmd->next == NULL)
            return;
        current_cmd = current_cmd->next;
    }
}

