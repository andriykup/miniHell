/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/05/26 15:01:35 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

void    quotes_out(char *dst, char *src)
{
    int i;

    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

char *get_env_value(const char *key, t_env *env)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

char *replace_dollar_sign(char *str, t_env *env)
{
    int i;
    int j;
    char *temp;
    char *res;
    
    temp = malloc(sizeof(char) * 100);
    if (temp == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0' && str[i] != '"')
        temp[i] = str[i++];
    temp[i] = '\0';
    res = get_env_value(temp + 1, env); // +1 to skip the $
    free(temp);
    if (res)
        return ft_strdup(res);
    return ft_strdup("");
}

char *dquotes_work(char *str, t_env *env)
{
    int i = 0;
    int j = 0;
    char *res = malloc(sizeof(char) * (ft_strlen(str) + 1));
    char *env_value;
    
    if (!res)
        return NULL;
    while (str[i] != '\0' && str[i] != '"')
    {
        if (str[i] == '$')
        {
            env_value = replace_dollar_sign(&str[i], env);
            if (env_value)
            {
               strncpy(&res[j], env_value, ft_strlen(env_value));
                j += ft_strlen(env_value);
                while (str[i] && !isspace(str[i]) && str[i] != '"')
                    i++;
                free(env_value);
                continue;
            }
        }
        res[j++] = str[i++];
    }
    res[j] = '\0';
    return res;
}
char   *command_quotes(char *str, t_commands *cmd, t_env *env)
{
    int i;
    int quotes;
    int dquotes;
    
    quotes = 0;
    dquotes = 0;
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
      return (NULL);
    return (str);
}



t_mini_shell   *commands_args(t_mini_shell *mini_shell, t_env *env)
{
    char **temp;
    int i;
    int j;
    int args;
    t_commands *cmd;
    
    cmd = mini_shell->commands;
    while (mini_shell->parsed_input[i] != NULL)
    {
        temp = ft_split(mini_shell->parsed_input[i], ' ');
        cmd = malloc(sizeof(t_commands));
        while (temp[j] != NULL)
        {
           cmd->args[args++] = command_quotes(temp[j], cmd, env);
           j++;
           args++;
        }
        i++;
        args = 0;
        j = 0;
    }
}
void add_node(void **head, void *new_node)
{
    void *temp;

    if (!*head)
    {
        *head = new_node;
    }
    else
    {
        temp = *head;
        while (*(void **)temp)
            temp = *(void **)temp;
        *(void **)temp = new_node;
    }
}
t_commands *create_command_node(char *cmd_str)
{
    t_commands *new_node;
    new_node = malloc(sizeof(t_commands));
    if (!new_node)
        return NULL;
    new_node->cmd = allocate_string(cmd_str);
    new_node->args = NULL;
    new_node->next = NULL;
    return new_node;
}