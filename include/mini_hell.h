/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:09:31 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/09 13:05:38 by aconvent         ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>
//#include <limits.h> //for mac

//main struct
typedef struct s_mini_shell
{
	int		pipes;
	char	*input;
	char	**parsed_input;
} t_mini_shell;

//struct for env var
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *prev;
	struct s_env *next;
} t_env;

void	mini_hell(t_mini_shell mini_shell);

//utils folder
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// commands
int		com_echo(char *str, int com_option);
char	*com_pwd(void);
char	*com_cd(void);
void com_export(t_env *head, char *new_env_var);
void com_env(t_env *head);
int com_unset(t_env **head, char *env);

//util for env
t_env *find_env_var(t_env *head, char *env);

// free functions
void	free_struct(t_mini_shell mini_shell);

// error handling functions
void	error(int error_code, t_mini_shell mini_shell);

#endif