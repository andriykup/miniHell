/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:04:38 by ankupins          #+#    #+#             */
/*   Updated: 2024/06/16 15:31:09 by aconvent         ###   ########.fr       */
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
	//printf("the probleme is here \n"); //note from aconvent, whhat is the problem? :D
	mini_hell(&mini_shell, my_env);
    return (0);
}

// extra functions

void free_command_struct(t_mini_shell *mini_shell)
{
	int i;

	i = 0;
	t_command *cmd;
	
	cmd = mini_shell->commands;
	while (cmd)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		if (cmd->redirected == true)
		{
			while(cmd->redir)
			{
				free(cmd->redir->file_name);
				free(cmd->redir->redir);
				cmd->redir = cmd->redir->next;
			}
		}
		cmd = cmd->next;
		i = 0;
	}
	free(cmd);
}
void free_struct(t_mini_shell *mini_shell)
{
	int i;
	i = 0;
	if (mini_shell->parsed_input)
	{
		while (mini_shell->parsed_input[i] != NULL)
		{
			free(mini_shell->parsed_input[i]);
			mini_shell->parsed_input[i] = NULL;
			i++;
		}
		free(mini_shell->parsed_input[i]);
		mini_shell->parsed_input[i] = NULL;
		free(mini_shell->parsed_input);
		mini_shell->parsed_input = NULL;
		free_command_struct(mini_shell);
	}
}
