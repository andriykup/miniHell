/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:44:08 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/16 16:21:21 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"



void    quotes_out(char *dst, char *src)
{
    int i;

    i = 0;
    if (src[i] == '\0')
    {
        dst[i] = '\0';
        return;
    }
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
    
    
    temp = malloc(sizeof(char) * (ft_strlen(str) + 1 ));
    if (temp == NULL)
        return (NULL);
    i = 1;
    j = 0;
    while (str[i] != '\0' && str[i] != '"' && str[i] != ' ')
    {
        temp[j] = str[i];
        i++;
        j++;
    }
    temp[j] = '\0';
    res = get_env_value(temp , env);
    free(temp);
    if (res)
        return res;
    return ft_strdup("");
}

size_t calculate_total_length(char *str, t_env *env)
{
    size_t total_length = 0;
    char *env_value;
    int i = 0;

    // todo check
    while (str[i] != '\0' && str[i] != '"') 
    {
        if (str[i] == '$') 
        {
            env_value = replace_dollar_sign(&str[i], env);
            if (env_value) 
            {
                total_length += ft_strlen(env_value) ;
                free(env_value);
                while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
                    i++;
                continue;
            }
        }
        total_length++;
        i++;
    }
    return total_length;
}

void dquotes_work(char *str, t_env *env)
{
    int i = 0, j = 0;
    size_t total_length = calculate_total_length(str, env);
    char *res = malloc(sizeof(char) * (total_length + 1));
    char *env_value;

    if (!res)
        return;
    printf("str = %s\n", str);
    while (str[i] != '\0' && str[i] != '"') 
    {
        if (str[i] == '$') 
        {
            env_value = replace_dollar_sign(&str[i], env);
            if (env_value) 
            {
                ft_strncpy(&res[j], env_value, ft_strlen(env_value));
                j += strlen(env_value);
                while (str[i] && !ft_isspace(str[i]) && str[i] != '"')
                {
                    i++;
                }
                continue;
            }
        }
        res[j++] = str[i++];
    }
    res[j] = '\0';
    ft_strncpy(str, res, total_length);
}


void ft_strncpy(char *dest, char *src, unsigned int n)
{
	int i;

	i = 0;

	while (src[i] && i <= n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i++] = '\0';
}