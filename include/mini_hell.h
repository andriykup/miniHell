/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:09:31 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/30 15:19:44 by aconvent         ###   ########.fr       */
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
//#include <linux/limits.h>
#include <stdbool.h>
#include <limits.h> //for mac

typedef struct s_redirection {
    char *file_name;
    char *redir;
    struct s_redirection *next;
    
} t_redir;

typedef struct s_command
{
	char **args;
    t_redir *redir;
    bool redirected;
    struct s_command *next;
} t_command;

//struct for env var

//main struct
typedef struct s_mini_shell
{
	int		pipes; // number of the pipes 
	char	**parsed_input;
	char *my_paths;
	char **splitted_paths;
	t_command *commands;
} t_mini_shell;


typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *prev;
	struct s_env *next;
} t_env;


t_command *command_list(t_mini_shell mini_shell);
void mini_hell(t_mini_shell mini_shell, t_env *my_env);


//parsing functions 
void add_redir_to_end(t_redir **head, t_redir *new_node);
void print_command_list(t_command *cmd);
//utils folder
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void ft_free_2arr(char **arr);


// commands
int		com_echo(char **command);
char	*com_pwd(char **command);
char	*com_cd(char *path); 
void empty_cd(t_env *head);
void	com_export(t_env *head, char *new_env_var);
void	com_env(char**command, t_env *head);
int		com_unset(t_env **head, char *env);
size_t	ft_strlen(const char *s);
void	com_exit(t_mini_shell mini_shell, t_env *my_env);

//util for env
t_env	*find_env_var(t_env *head, char *env);
void	*set_my_env(char **environ, t_env **head);
void	my_simple_execve(t_mini_shell mini_shell);
char	*find_cmd_path(char **paths_envp, char *cmd);
void	simple_execution(t_mini_shell mini_shell, t_env *my_env);
char	*get_env_path(t_env *my_env);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);

// free functions
void	free_struct(t_mini_shell mini_shell);
void free_my_env(t_env *head);

// error handling functions
void	error(int error_code, t_mini_shell mini_shell);

#endif