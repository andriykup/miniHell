/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:19:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/15 03:35:15 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// remove simple executions function
// adapt exit
// adjust char *my_paths; from the structure ++
// 	t_env better to be inside of t_mini_shell
// return value of bulld in functions for echo function
// fix empty arguments for cd function and home directory
//  

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
		free(ret);
		i++;
	}
	free(full_cmd);
	return (NULL);
}
	//execve need to work with pat (/bin/ls)

void multi_pipe_executions(t_mini_shell mini_shell, t_env *my_env)
{
	char **splitted_paths = ft_split(mini_shell.my_paths, ':');  // splitted_paths should be part of struct (t_mini_shell mini_shell) 
	// split args of each command
	// char	**cmd_args1 = ft_split(mini_shell.parsed_input[0], ' ');
	// char	**cmd_args2 = ft_split(mini_shell.parsed_input[1], ' ');
	// char *cmd_path1 = find_cmd_path(splitted_paths, cmd_args1[0]);
	// char *cmd_path2 = find_cmd_path(splitted_paths, cmd_args2[0]);
	
	int num_commands = mini_shell.pipes + 1;
	int pipefd[2 * mini_shell.pipes];
	//setting pipes
	int i = 0;
	while(i < mini_shell.pipes)
	{
		pipe(pipefd + 2 * i); //why this formula??
		i++;
		//missing protection
	}


	i = 0;
	while(i < num_commands)
	{
		int pid = fork();
		if(pid == 0)
		{

				//if not the first command
			if(i != 0)
			{
				dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
				//missing protection
			}
				//if not the last command
			if(i != num_commands - 1) //why '-1'??
			{
				dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
			}

			// Close all pipe file descriptors
			int j = 0;
			while(j < 2 * (num_commands - 1))
			{
				close(pipefd[j]);
				j++;
			}
			char	**cmd_args = ft_split(mini_shell.parsed_input[i], ' ');
			char	*cmd_path = find_cmd_path(splitted_paths, cmd_args[0]);
			
			execve(cmd_path, cmd_args, NULL);
			
			//missing protection
		}
		i++;
	}
 
	i = 0;
	while(i < 2 * (num_commands - 1)) //why '-1'??
	{
		close(pipefd[i]);
		i++;
	}
	i = 0;
	while(i < num_commands)
	{
		wait(NULL);
		i++;
	}
}


void my_simple_execve(t_mini_shell mini_shell)
{
	int pid;
	char	*cmd_path;
	char	**cmd_args;
	char **splitted_paths = ft_split(mini_shell.my_paths, ':'); // splitted_paths should be part of struct (t_mini_shell mini_shell) 

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
		if((execve(cmd_path, cmd_args, NULL)) < 0)
		{
			// added check for the exit input
			printf("minishell: command not found: %s\n", cmd_args[0]);
			exit(EXIT_SUCCESS);
		}
	}
	wait(NULL); // not sure abou wait(), check this part better
	ft_free_2arr(splitted_paths);
	ft_free_2arr(cmd_args);
	free(cmd_path);
}

void	simple_execution(t_mini_shell mini_shell, t_env *my_env)
{
	char **command;
	
	command = ft_split(mini_shell.parsed_input[0], ' ');
	if (command == NULL)
	{
		//error mannaging
		printf("error in the creation of the split\n");
		return ;
	}
	if(ft_strncmp(command[0], "echo", 5) == 0)
	 	com_echo(command);
	else if (ft_strncmp(command[0], "cd", 3) == 0)
	{
		if(command[1] != NULL)
			com_cd(command[1]);
			//if value is empty, need to go to home dir
	}
	else if (ft_strncmp(command[0], "env", 4) == 0)
	 	com_env(command, my_env);
	else if (ft_strncmp(command[0], "unset", 6) == 0)
		com_unset(&my_env, command[1]);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
	 	com_pwd(command);
	else if (ft_strncmp(command[0], "export", 7) == 0)
		com_export(my_env, command[1]);
	else if (ft_strncmp(command[0], "exit", 7) == 0)
	{
		ft_free_2arr(command);
		com_exit(mini_shell, my_env);
	}
	else
		my_simple_execve(mini_shell);
	ft_free_2arr(command);
}

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
		multi_pipe_executions(mini_shell, my_env);
}


char *ft_spaceout(char *input)
{
	char *res;
	int len;
	int i;
	int j;
	
	i = 0;
	j = 0;
	len = ft_strlen(input);
	res = malloc(sizeof(char) * (len + 1));
	while (input[i] == ' ' && input[i] != '\0')
		i++;
	while (input[i] != '\0')
		res[j++] = input[i++];
	res[j] = '\0';
	free(input);
	return (res);
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
		input = ft_spaceout(input);
		printf("string = [%s]\n", input);
		mini_shell.parsed_input = ft_split(input, '|');// need to adjust for min_shell
		if (mini_shell.parsed_input[0] == NULL)
			continue;
		free(input);
		while (mini_shell.parsed_input[i++] != NULL)
			mini_shell.pipes++;
		check_pipes(mini_shell, my_env);
		free_struct(mini_shell);
	}	
}

