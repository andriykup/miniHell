/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:48:47 by ankupins          #+#    #+#             */
/*   Updated: 2024/06/03 14:39:48 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

// option '-n' -> com_option == 1
// without option  -> com_option == 0

int com_echo(char **command)
{
	int flag;
	int i;
	
	flag = 0;
	i = 1;
	if (command[i] == NULL)
	{
		printf("\n");
		return(0);
	}
	while (ft_strncmp(command[i], "-n", 3) == 0)
	{
		flag = 1;
		if (command[++i] == NULL)
			return(0);
	}
	while (command[i] != NULL)
	{
		printf("%s", command[i]);
		if (command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (flag == 0)
	printf("\n");
	return (0);
}
