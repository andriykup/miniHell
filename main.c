/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:04:38 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 13:23:48 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mini_hell.h"
int main()
{
	t_mini_shell mini_shell;
    //t_env *my_env;
	//extern char **environ;

 	//my_env = NULL;
   //set_my_env(environ, &my_env);

	mini_shell.input = NULL;
	mini_shell.parsed_input = NULL;

	mini_hell(mini_shell);
    return (0);
}



// extra functions


void free_struct(t_mini_shell mini_shell)
{
	int i;
	i = 0;
	if (mini_shell.input)
		free (mini_shell.input);
	if (mini_shell.parsed_input)
	{
		while (mini_shell.parsed_input[i] != NULL)
		{
			free(mini_shell.parsed_input[i]);
			i++;
		}
		free(mini_shell.parsed_input);
	}
}