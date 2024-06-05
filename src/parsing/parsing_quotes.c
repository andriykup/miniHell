/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:44:08 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/05 13:05:30 by aconvent         ###   ########.fr       */
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

char *replace_dollar_sign(char *str, t_env *env)
{
    int i;
    int j;
    char *temp;
    char *res;
    
    
    temp = malloc(sizeof(char) * 100000);
    if (temp == NULL)
        return (NULL);
    i = 0;
    while (str[i] != '\0' && str[i] != '"')
    {
        temp[i] = str[i];
        i++;
    }
    temp[i] = '\0';
    res = get_env_value(temp , env); 
    free(temp);
    if (res)
        return ft_strdup(res);
    return ft_strdup("");
}

void dquotes_work(char *str, t_env *env)
{
    int i;
    int j;
    char *res;
    char *env_value;
    
    i = 0;
    j = 0;
    res = malloc(sizeof(char *) * (ft_strlen(str) + 1));
    
    if (!res)
        return;
    while (str[i] != '\0' && str[i] != '"') 
    {
        if (str[i] == '$') 
        {
            env_value = replace_dollar_sign(&str[i + 1], env);
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
