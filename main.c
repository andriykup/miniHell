/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:04:38 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/14 20:58:08 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mini_hell.h"
int main()
{
	t_mini_shell mini_shell;
    t_env *my_env;
	extern char **environ;

 	my_env = NULL;
	set_my_env(environ, &my_env);
	mini_shell.parsed_input = NULL;
	mini_shell.pipes = -1;
	mini_shell.my_paths = get_env_path(my_env);
	mini_hell(mini_shell, my_env);
    return (0);
}

// extra functions


void free_struct(t_mini_shell mini_shell)
{
	int i;
	i = 0;
	if (mini_shell.parsed_input)
	{
		while (mini_shell.parsed_input[i] != NULL)
		{
			free(mini_shell.parsed_input[i]);
			mini_shell.parsed_input[i] = NULL;
			i++;
		}
		free(mini_shell.parsed_input[i]);
		mini_shell.parsed_input[i] = NULL;
		free(mini_shell.parsed_input);
		mini_shell.parsed_input = NULL;
	}
}
