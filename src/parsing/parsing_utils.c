/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:47:40 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/05 13:14:07 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"


bool is_quotes(char c)
{
    return (c == '\'' || c == '\"');
}

bool token_delimiter(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '<' || c == '>');
}

void skip_spaces(char *str, int *i)
{
    while (str[*i] == ' '  || (str[*i] >= 9 && str[*i] <= 13))
        (*i)++;
}

void skip_quotes(char *str, int *i)
{
    char quote;
    quote = str[*i];
    (*i)++;
    while (str[*i] != quote && str[*i] != '\0') 
    {
        (*i)++;
    }
    if (str[*i] == quote)
        (*i)++;
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
