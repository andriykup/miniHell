/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:48:47 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/14 13:48:26 by amaury           ###   ########.fr       */
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
		i++;
		if (command[i] == NULL)
			return(0);
	}
	while (command[i] != NULL)
	{
		printf("%s", command[i]);
		i++;
		if (command[i] != NULL)
			printf(" ");
	}
	if (flag == 0)
	printf("\n");
	return (0);
}

// int main()
// {
// 	com_echo("-", 0);
// 	return 0;
// }


// echo "-" ----> edge case
//echo "\a" --> edge case