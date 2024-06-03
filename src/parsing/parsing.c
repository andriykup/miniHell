/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:26:03 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/03 13:09:19 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"



//dequoting file name but not redir in t_redir 

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
    {
        temp[i] = str[i];
        i++;
    }
    temp[i] = '\0';
    res = get_env_value(temp + 1, env); 
    free(temp);
    if (res)
        return ft_strdup(res);
    return ft_strdup("");
}

void dquotes_work(char *str, t_env *env) 
{
    int i = 0;
    int j = 0;
    char *res = malloc(sizeof(char) * (ft_strlen(str) + 1));
    char *env_value;

    if (!res)
        return;

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
    strncpy(str, res, ft_strlen(res) + 1);
    free(res);
}
char   *command_quotes(char *str, t_env *env)
{
    int i;
    bool quotes;
    bool dquotes;
    
    quotes = true;
    dquotes = true;
    i = 0;
    while (str[i])
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
        i++;
    }
    if (!quotes || !dquotes)
      return (NULL);
    return (ft_strdup(str));
}



void parse_quotes_args(t_mini_shell mini_shell, t_env *env) {
    t_command *current_cmd ;
    char *processed_arg;
    int i;
    
    current_cmd = mini_shell.commands;
    while (current_cmd) {
        i = 0;
        while (current_cmd->args && current_cmd->args[i]) 
        {
            processed_arg = command_quotes(current_cmd->args[i], env);
            printf("the arg = %s", processed_arg);
            if (processed_arg) 
            {
                free(current_cmd->args[i]); // Free the original argument
                current_cmd->args[i] = processed_arg; // Update with the processed argument
            } 
            else 
            {
                // Handle error: unmatched quotes or other issues
                // You can choose to set the argument to an empty string or handle it differently
            }
            i++;
        }
        current_cmd = current_cmd->next;
    }
}
