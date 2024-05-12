/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:19:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/12 16:27:27 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_hell.h"

/*
	if(mini_shell.pipes == 0)
	{
		function to check input
	} 
	else
	{
		execute pipex functions etc
	}
	command for each commands ! 
*/

char	*find_cmd_path(char **paths_envp, char *cmd)
{
	int		i;
	char	*full_cmd;
	char	*ret;

	if (paths_envp == NULL)
		return (NULL);
	full_cmd = ft_strjoin("/", cmd);
	if (full_cmd == NULL)
		return (NULL);
	i = 0;
	while (paths_envp[i])
	{
		ret = ft_strjoin(paths_envp[i], full_cmd);
		if (access(ret, X_OK) != -1)
		{
			free(full_cmd);
			return (ret);
		}
		i++;
	}
	free(ret);
	free(full_cmd);
	return (NULL);
}

void my_simple_execve(t_mini_shell mini_shell, char *my_paths)
{
	int pid;
	char	*cmd_path;
	char	**cmd_args;
	char **splitted_paths = ft_split(my_paths, ':');

	cmd_args = ft_split(mini_shell.parsed_input[0], ' ');
	cmd_path = find_cmd_path(splitted_paths, cmd_args[0]);

	if (cmd_path == NULL)
	{
		free(cmd_args);
		//printf("ERROR\n");
		//exit_error("error cmd_path");
	}

	pid = fork();
	if(pid == -1)
		printf("error forking");
		//exit_error
	if(pid == 0)
	{
		if((execve(cmd_path, cmd_args, NULL)) == -1)
			printf("minishell: command not found: %s\n", mini_shell.parsed_input[0]);
			//exit_error("excve child 2 error");
	}
	wait(NULL); // not sure abou wait(), check this part better
}

void	simple_execution(t_mini_shell mini_shell, t_env *my_env)
{
	char *my_paths = get_env_path(my_env);
	// if(ft_strncmp(mini_shell.parsed_input, "echo ", 5) == 0)
	// 	com_echo();
	// else if (ft_strncmp(mini_shell.parsed_input, "cd ", 3) == 0)
	// 	com_cd();
	// else if (ft_strncmp(mini_shell.parsed_input, "env ", 4) == 0)
	// 	com_env();
	// else if (ft_strncmp(mini_shell.parsed_input, "unset ", 6) == 0)
	// 	com_unset();
	// else if (ft_strncmp(mini_shell.parsed_input, "pwd ", 4) == 0)
	// 	com_cd();
	// else if (ft_strncmp(mini_shell.parsed_input, "export ", 7) == 0)
	// 	com_cd();
	// else
	// {
		my_simple_execve(mini_shell, my_paths);
//	}
	
	free(my_paths);
}

// void	check_pipes(t_mini_shell mini_shell)
// {
// 	if (mini_shell.pipes == 0)
// 		simple_execution(mini_shell);
// 	else
// 		printf("not there yet\n");
// }


char	*get_env_path(t_env *my_env)
{
	char *env_path;
    t_env *current = my_env;

    while (current != NULL)
    {
        if(ft_strncmp(current->key, "PATH", 4) == 0)
		{
			env_path = ft_strdup(current->value);
			return (env_path);
		}
        current = current->next;
    }
	return (NULL);
}


void	check_pipes(t_mini_shell mini_shell, t_env *my_env)
{
	if (mini_shell.pipes == 0)
		simple_execution(mini_shell, my_env);
	else
		printf("not there yet\n");
}
void mini_hell(t_mini_shell mini_shell, t_env *my_env)
{
	int i;
	char *input;
	while (1)
	{
		i = 0;
		mini_shell.pipes = -1;
		input = readline("Enter a line: ");
		if (input[0] != '\0')
			add_history(input);
		mini_shell.parsed_input = ft_split(input, '|');// need to adjust for min_shell
		free(input);
		while (mini_shell.parsed_input[i] != NULL)
		{
			mini_shell.pipes++;
			i++;
		}
		check_pipes(mini_shell, my_env);
		if (mini_shell.parsed_input[0] && (ft_strncmp(mini_shell.parsed_input[0] , "exit", 6) == 0))
		{
			free_struct(mini_shell);
			exit (0);
		}
		free_struct(mini_shell);
	}	
}

// t_commands 
// {
// 	char * cmd_flags;
// }