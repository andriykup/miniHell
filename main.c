/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:04:38 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/25 12:29:16 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mini_hell.h"
int main()
{
	t_mini_shell mini_shell;

	mini_shell.input = readline("Enter a line: ");

	printf("the string is %s", mini_shell.input);
	int i = 0;

	free_struct(mini_shell);
    return (0);
}


void free_struct(t_mini_shell mini_shell)
{
	if (mini_shell.input)
		free (mini_shell.input);
}
void user_input()
{

}