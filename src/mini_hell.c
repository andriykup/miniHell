/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:19:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/06/05 12:39:20 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return value of bulld in functions for echo function

#include "../include/mini_hell.h"

char	*find_cmd_path(char **paths_envp, char *cmd)
{
	int		i;
	char	*full_cmd;
	char	*ret;

	ret = NULL;
	full_cmd = NULL;
	if (paths_envp == NULL || cmd == NULL)
		return (NULL);
	if(cmd[0] == '/')
	{
		if (access(cmd, X_OK) != -1)
		{
			ret = ft_strdup(cmd);
			if(ret == NULL)
				return NULL;
		return (ret);
		}
		return (NULL);
	}
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

int ft_my_env_length(t_env *my_env)
{
	t_env *current;
	current = my_env;
	int i;

	i = 0;
	while(current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	*ft_strjoin_environ(char const *s1, char const *s2)
{
	int		i;
	int		ret_i;
	char	*ret;
	int		length;

	length = ft_length(s1, s2);
	ret = (char *)malloc((length + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	ret_i = 0;
	if(s1 != NULL)
	{
		while (s1[ret_i])
		{
			ret[ret_i] = s1[ret_i];
			ret_i++;
		}
	}
	ret[ret_i++] = '=';
	i = 0;
	if(s2 != NULL)
	{
		while (s2[i])
		{
			ret[ret_i] = s2[i];
			i++;
			ret_i++;
		}
	}
	ret[ret_i] = '\0';
	return (ret);
}

void ft_local_environ(t_mini_shell *mini_shell, t_env *my_env)
{
	//create local environ
	// if its NULL create it, if not NULL free and create again
	t_env *current;
	current = my_env;
	int my_env_length;
	int i;
	
	i = 0;
	if(mini_shell->local_environ != NULL)
	{
		printf("test\n\n");
		ft_free_2arr(mini_shell->local_environ);
	}
	my_env_length = ft_my_env_length(my_env);
	mini_shell->local_environ = malloc(sizeof(char *) * (my_env_length + 1));
	while(current)
	{
		mini_shell->local_environ[i] = ft_strjoin_environ(current->key, current->value);
		i++;
		current = current->next;
	}
	mini_shell->local_environ[i] = NULL;
}

void my_executions(t_mini_shell mini_shell, t_env *my_env)
{
	int pipefd[2 * mini_shell.pipes];
	int pid;
	t_command *command_current = mini_shell.commands;
	char	*cmd_path;
	int i;
	
	mini_shell.splitted_paths = ft_split(mini_shell.my_paths, ':');  // splitted_paths should be part of struct (t_mini_shell mini_shell) 
	create_pipes(pipefd, mini_shell); //create pipes
	i = 0;
	ft_local_environ(&mini_shell, my_env);
	while(i < (mini_shell.pipes + 1))
	{
		if(builtin_com(mini_shell, my_env, command_current->args) == 1)
			return ;
		pid = fork();
		if(pid == 0)
		{
			if(i != 0)  //if not the first command
			{
				if(dup2(pipefd[(i - 1) * 2], STDIN_FILENO) == -1)
				{
					perror("dup2 failuer");
					exit(EXIT_FAILURE);
				}
			}
			if(i != mini_shell.pipes) //if not the last command
			{
				if(dup2(pipefd[i * 2 + 1], STDOUT_FILENO) == -1)
				{
					perror("dup2 failuer");
					exit(EXIT_FAILURE);
				}
			}
			int j = 0;
			while(j < 2 * (mini_shell.pipes)) // Close all pipe file descriptors
			{
				close(pipefd[j]);
				j++;
			}
			if(builtin_com_pipe(mini_shell, my_env, command_current->args) == 1)
				exit (0);
			else
			{
				cmd_path = find_cmd_path(mini_shell.splitted_paths, command_current->args[0]);
				if((execve(cmd_path, command_current->args, mini_shell.local_environ)) < 0)
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
	while(i < 2 * mini_shell.pipes)
	{
		close(pipefd[i]);
		i++;
	}
	i = 0;
	while(i < mini_shell.pipes + 1)
	{
		wait(NULL);
		i++;
	}
	ft_free_2arr(mini_shell.local_environ);
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
		mini_shell.parsed_input = ft_split(input, '|');
		free(input);
		if (mini_shell.parsed_input[0] == NULL)
			continue;
		while (mini_shell.parsed_input[i++] != NULL)
			mini_shell.pipes++;
		mini_shell.commands = command_list(mini_shell);
		parse_quotes_args(mini_shell, my_env);

		my_executions(mini_shell, my_env);
		free_struct(mini_shell);
	}	
}

