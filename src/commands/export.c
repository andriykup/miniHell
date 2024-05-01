/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankupins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:30:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/04/28 11:30:55 by ankupins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_hell.h"
// setenv, putenv, and clearenv  <<<<-----
char *com_export(char *env)
{
    extern char **environ;
    
    printf("%s\n", environ[1]);

    //  set environment variables and make them available to child processes
    //  To set an environment variable and make it available to subprocesses, use the export
    //  export MY_VAR="Hello, World!" 
}
// --->    getenv - is allowed
// find_env_var() will be useful to check if env_var already exist

// int add_new_env(t_com_export *head, char *env)
// {

// } 

// t_com_export *find_env_var(t_com_export *head, char *env)
// {


// }

int main()
{
    com_export();

    return 0;
}
