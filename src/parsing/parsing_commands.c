/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:44:16 by aconvent          #+#    #+#             */
/*   Updated: 2024/06/23 15:26:32 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

 
char *tokenizing(char *input, int *i)
{
    int saved;
    char *res;

    saved = *i;
    while (input[*i] && !token_delimiter(input[*i])) 
    {
        if (is_quotes(input[*i]))
            skip_quotes(input, i);
        else
            (*i)++;
    }
    res = ft_substr(input, saved, (*i - saved));
    if (!res) 
    {
        // error management
    }
    return res;
}

t_redir *get_redir(char *str, int *i)
{
    t_redir *redi;
    int j;

    j = 0;
    redi = redir_init();
    if (str[*i] == '<')
        redi->redir = strdup("<");
    else if (str[(*i)++] == '>') 
    {
        if (str[*i] == '>')
            redi->redir = strdup(">>");
        else
            redi->redir = strdup(">");
    }
    skip_spaces(str, i);
    redi->file_name = tokenizing(str, i);
    return redi;
}

void get_command(char *input, t_command **cmd, t_env *env)
{
    int j = 0;
    int i = 0;
    t_redir *redir;
    char *temp;

    (*cmd)->args = malloc(sizeof(char *) * (1000)); 
    if (!(*cmd)->args)
        return;
    while (input[i]) 
    {
        skip_spaces(input, &i);
        if (input[i] != '<' && input[i] != '>' && input[i] != '\0')
        {
            temp = tokenizing(input, &i);
            (*cmd)->args[j] = malloc(sizeof(char) * (calculate_total_length(temp, env)+ 1 ));
            (*cmd)->args[j] = ft_strdup(temp);
            if ( (*cmd)->args[j] == NULL)
            {
                exit(0);
            }
            free(temp);
            j++;
        }
        else if ((input[i] == '<' || input[i] == '>') && input[i] != '\0')
        {
            (*cmd)->redirected = true;
            redir = get_redir(input, &i);
            add_redir_to_end(&(*cmd)->redir, redir);
        }
        skip_spaces(input, &i);
    }
    (*cmd)->args[j] = NULL;
}
