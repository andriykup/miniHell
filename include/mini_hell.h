/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:09:31 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 11:09:33 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_HELL_H
#define MINI_HELL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_mini_shell
{
    char *input;
    char **parsed_input;
} t_mini_shell;


#endif