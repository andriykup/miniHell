/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:09:31 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 12:41:31 by aconvent         ###   ########.fr       */
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

typedef struct s_mini_shell
{
    char *input;
    char **parsed_input;
} t_mini_shell;

void free_struct(t_mini_shell mini_shell);

#endif