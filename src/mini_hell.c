/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:19:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/06/16 16:36:21 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return value of bulld in functions for echo function

//error after integrating ne parsing!!!
		// exit
		// minishell(21756,0x206003ac0) malloc: *** error for object 0x27e9cfe9c80: pointer being freed was not allocated
		// minishell(21756,0x206003ac0) malloc: *** set a breakpoint in malloc_error_break to debug
		// zsh: abort      ./minishell
////

#include "../include/mini_hell.h"

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
	
	////////////////
	
	int builtin_com(t_mini_shell mini_shell, t_env *my_env, char **cmd_args)
	{
		if (ft_strncmp(cmd_args[0], "export", 7) == 0)
		{
			com_export(my_env, cmd_args[1]);
			return 1;
		}
		else if (ft_strncmp(cmd_args[0], "unset", 6) == 0)
		{
			com_unset(&my_env, cmd_args[1]);
			return 1;
		}
		else if (ft_strncmp(cmd_args[0], "cd", 3) == 0)
		{
			if(cmd_args[1] == NULL)
				empty_cd(my_env);
			else
				com_cd(cmd_args[1]);
			return 1;
		}
		else if (ft_strncmp(cmd_args[0], "exit", 7) == 0)
		{
			printf("exit\n");
			ft_free_2arr(cmd_args);
			com_exit(mini_shell, my_env);
		}
		return 0;
	}

	int builtin_com_pipe(t_mini_shell mini_shell, t_env *my_env, char **cmd_args)
	{
			if (ft_strncmp(cmd_args[0], "env", 4) == 0)
			{
	 			com_env(cmd_args, my_env);
				return 1;
			}
			else if (ft_strncmp(cmd_args[0], "pwd", 4) == 0)
			{
	 			com_pwd(cmd_args);
				return 1;
			}
			else if(ft_strncmp(cmd_args[0], "echo", 5) == 0)
			{
				com_echo(cmd_args);
				return 1;
			}
		return 0;
	}

	void create_pipes(int *pipefd, t_mini_shell mini_shell)
	{
		int i;

		i = 0;
		while(i < mini_shell.pipes)
		{
			if (pipe(pipefd + 2 * i) == -1)
        	{
           		perror("pipe");
				printf("\nPIPE creation Error\n"); //checker
            	exit(EXIT_FAILURE);
        	}
			i++;
		}
	}
	


	//execve need to work with pat (/bin/ls) <<-----------------

void my_executions(t_mini_shell *mini_shell, t_env *my_env)
{
	int pipefd[2 * mini_shell->pipes];
	int pid;
	t_command *command_current = mini_shell->commands;
	//char	**cmd_args; //delete
	char	*cmd_path;
	int i;
	
	mini_shell->splitted_paths = ft_split(mini_shell->my_paths, ':');  // splitted_paths should be part of struct (t_mini_shell mini_shell) 
	create_pipes(pipefd, *mini_shell); //create pipes
	i = 0;
	while(i < (mini_shell->pipes + 1))
	{
		//cmd_args = ft_split(mini_shell.parsed_input[i], ' '); //delete, its already part of the struct
		if(builtin_com(*mini_shell, my_env, command_current->args) == 1)
			return ;
		pid = fork();
		if(pid == 0)
		{
			if(i != 0)  //if not the first command
			{
				dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
				//missing protection
			}
			if(i != mini_shell->pipes) //if not the last command
			{
				dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
			}
			int j = 0;
			while(j < 2 * (mini_shell->pipes)) // Close all pipe file descriptors
			{
				close(pipefd[j]);
				j++;
			}
			if(builtin_com_pipe(*mini_shell, my_env, command_current->args) == 1)
				exit (0);
			else
			{
				cmd_path = find_cmd_path(mini_shell->splitted_paths, command_current->args[0]);
				if((execve(cmd_path, command_current->args, NULL)) < 0)
				{
					printf("minishell: command not found: %s\n", command_current->args[0]);
					exit(0);
				}
			}
		}
		command_current = command_current->next;
		i++;
	}
	i = 0;
	while(i < 2 * mini_shell->pipes)
	{
		close(pipefd[i]);
		i++;
	}
	i = 0;
	while(i < mini_shell->pipes + 1)
	{
		wait(NULL);
		i++;
	}
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

void mini_hell(t_mini_shell *mini_shell, t_env *my_env)
{
	int i;
	char *input;
	while (1)
	{
		i = 0;
		mini_shell->pipes = -1;
		input = readline("Enter a line: ");
		if (input[0] != '\0')
			add_history(input);
		input = ft_spaceout(input);
		mini_shell->parsed_input = ft_split(input, '|');
		free(input);
		if (mini_shell->parsed_input[0] == NULL)
			continue;
		while (mini_shell->parsed_input[i++] != NULL)
			mini_shell->pipes++;
		mini_shell->commands = command_list(mini_shell);
		parse_quotes_args(&mini_shell, my_env);
		my_executions(mini_shell, my_env);
		printf("\n\n");
		//free_struct(mini_shell);
	}	
}

