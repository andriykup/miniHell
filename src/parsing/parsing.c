/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/23 15:22:00 by aconvent         ###   ########.fr       */
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
            quotes_out(&str[i], &str[i + 1]);
            printf("str = %s\t %i\n", &str[i], i);
            dquotes_work(str, env);
        }
    }
    printf("str = %s\t %i\n", str, dquotes);
    if (!quotes || !dquotes)
    {
        printf("i entered here\n");
        return (ft_strdup(""));
    }
    str[i] = '\0';
    return (ft_strdup(str));
}

void    print_args(t_command command)
{
    int i;

    i = 0;
    while (command.args[i])
    {
        printf("\nthe arg[%i] = %s\n", i , command.args[i]);
        i++;
    }
}
void    print_struct(t_command *command)
{
    while (command != NULL)
    {
        print_args(*command);
        if (command->next != NULL)
        printf("---------nex command--------\n\n");
        command = command->next;       
    }
    printf("________________________--\n");
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
    print_struct(cmd_head);
    return cmd_head;
}
void parse_quotes_args(t_command *current_cmd, t_env *env)
{
    char *processed_arg;
    int i;
    
    while (current_cmd != NULL) 
    {
        i = -1;
        printf("i am here\n");
        while (current_cmd->args[++i] != NULL) 
        {
            processed_arg = command_quotes(current_cmd->args[i], env);
            if (processed_arg) 
            {
               (current_cmd)->args[i] = ft_strdup(processed_arg);
               //printf("(*current_cmd)->args[i] = %s\n",current_cmd->args[i]);
                free(processed_arg);
            }
        }
        if (current_cmd->next == NULL)
        {
            printf("\ni got here dszzz\n");
            return;
        }
        current_cmd = current_cmd->next;
        printf("i got here \n ");
    }
}

