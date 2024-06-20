/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:48:47 by ankupins          #+#    #+#             */
/*   Updated: 2024/06/20 11:13:54 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

// option '-n' -> com_option == 1
// without option  -> com_option == 0

int com_echo(char **command)
{
	int flag;
	int i;
	int j;
	
	flag = 0;
	i = 1;
	j = 2;
	
	if (command[i] == NULL)
	{
		printf("\n");
		return(0);
	}
	if (ft_strncmp(command[i], "-n", 2) == 0)
	{
		flag = 1;
		while(command[i][j] == 'n' )
			j++;
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
