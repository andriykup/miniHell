/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:19:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 13:33:20 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_hell.h"

void mini_hell(t_mini_shell mini_shell)
{
	int i = 0;
	while (1)
	{
		mini_shell.input = readline("Enter a line: ");
		printf("the string is %s\n", mini_shell.input);
		mini_shell.parsed_input = ft_split(mini_shell.input, ' ');// need to adjust for min_shell
		while (mini_shell.parsed_input[i] != NULL)
		{

			printf("%s\n", mini_shell.parsed_input[i]);
			i++;
		}
		if (mini_shell.parsed_input[0] && (ft_strncmp(mini_shell.parsed_input[0] , "exit", 6) == 0))
		{
			printf("i exit the program now\n");
			exit (0);
		}
		free_struct(mini_shell);
	}	
}