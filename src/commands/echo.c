/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:48:47 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/27 13:48:49 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"

// option '-n' -> com_option == 1
// without option  -> com_option == 0

int com_echo(char *str, int com_option)
{
	if (com_option == 0) // just 'echo'
		printf("%s\n", str);
	else if (com_option == 1) // with '-n' option
		printf("%s", str);
	return (0);
}

// int main()
// {
// 	com_echo("-", 0);
// 	return 0;
// }


// echo "-" ----> edge case
//echo "\a" --> edge case