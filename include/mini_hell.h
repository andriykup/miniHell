/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:09:31 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/14 14:43:52 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_HELL_H
#define MINI_HELL_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>
#include <limits.h> //for mac

typedef struct s_arguments
{
	char *arg;
	int quotes; //0 no quotes 1 single 2 double quotes
	struct s_arguments *next;
}	t_arguments;

typedef struct s_commands
{
	char *cmd;
	t_arguments *args;
	struct s_commands *next;
} t_commands;
//struct for env var

//main struct
typedef struct s_mini_shell
{
	int		pipes; // number of the pipes 
	char	**parsed_input;
	char *my_paths;
	t_commands *commands;
} t_mini_shell;


typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *prev;
	struct s_env *next;
} t_env;

void mini_hell(t_mini_shell mini_shell, t_env *my_env);

//utils folder
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void ft_free_2arr(char **arr);


// commands
int		com_echo(char **command);
char	*com_pwd(char **command);
char	*com_cd(char *path); 
void	com_export(t_env *head, char *new_env_var);
void com_env(char**command, t_env *head);
int com_unset(t_env **head, char *env);
size_t	ft_strlen(const char *s);
void com_exit(t_mini_shell mini_shell, t_env *my_env);

//util for env
t_env	*find_env_var(t_env *head, char *env);
void	*set_my_env(char **environ, t_env **head);
void	my_simple_execve(t_mini_shell mini_shell, char *my_paths);
char	*find_cmd_path(char **paths_envp, char *cmd);
void	simple_execution(t_mini_shell mini_shell, t_env *my_env);
char	*get_env_path(t_env *my_env);
char	*ft_strjoin(char const *s1, char const *s2);


// free functions
void	free_struct(t_mini_shell mini_shell);
void free_my_env(t_env *head);

// error handling functions
void	error(int error_code, t_mini_shell mini_shell);

#endif