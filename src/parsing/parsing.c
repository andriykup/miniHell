/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/05/26 09:56:45 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

void    quotes_out(char *dst, char *src)
{
    int i;

    i =0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

char *replace_dollar_sign(char *str, t_env *env)
{
    int i;
    int j;
    char *temp;
    
    temp = malloc(sizeof(char) * 100);
    if (temp == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0' && str[i] != '"' && !ft_isspace(str[i]))
        temp[i] = str[i];

    
}
char    *dquotes_work(char *str, t_env *env)
{
    int i;
    char *res;

    if (!res)
        return (NULL);
    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            replace_dollar_sign(&str[i], env);
    }
    
}
int  command_quotes(char *str, t_commands *cmd, t_env *env)
{
    int i;
    bool quotes;
    bool dquotes;
    
    quotes = true;
    dquotes = true;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' && dquotes)
        {
            quotes = !quotes;
            quotes_out(&str[i], &str[i + 1]);
        }
        else if (str[i] == '"' && quotes)
        {
            dquotes = !dquotes;
            if (dquotes_work(&str[i + 1], env) == NULL)
            {
                //error management
            }
            quotes_out(&str[i], &str[i + 1]);
        }
        i++;
    }
    if (!quotes || !dquotes)
       return (-1);
    return (0);
}



t_mini_shell   *commands_args(t_mini_shell *mini_shell, t_env *env)
{
    char **temp;
    int i;
    int j;
    t_commands *cmd;
    t_arguments *args;
    
    cmd = mini_shell->commands;
    while (mini_shell->parsed_input[i] != NULL)
    {
        temp = ft_split(mini_shell->parsed_input[i], ' ');
        cmd = malloc(sizeof(t_commands));
        while (temp[j] != NULL)
        {
           ft_checkquotes(temp, cmd, env);
        }
        i++;
        j = 0;
    
    }
}
