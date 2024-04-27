/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:09:31 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 13:24:03 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_HELL_H
#define MINI_HELL_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <linux/limits.h>

typedef struct s_mini_shell
{
    char *input;
    char **parsed_input;
} t_mini_shell;

void mini_hell(t_mini_shell mini_shell);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// commands
int com_echo(char *str, int com_option);
char *com_pwd(void);
char *com_cd(void);

// free functions
void free_struct(t_mini_shell mini_shell);

// error handling functions
void error(int error_code, t_mini_shell mini_shell);

#endif