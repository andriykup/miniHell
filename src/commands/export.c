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


//// -----------------------------
//int set_my_env(char **environ, t_env *head);


////------------------


#include "../../include/mini_hell.h"
// setenv, putenv, and clearenv  <<<<-----
// char *com_export(char *env)
// {
//     extern char **environ;
//     t_env *my_env;

//     my_env = set_my_env(environ, my_env);

    //  set environment variables and make them available to child processes
    //  To set an environment variable and make it available to subprocesses, use the export
    //  export MY_VAR="Hello, World!" 
// }
// --->    getenv - is allowed
// find_env_var() will be useful to check if env_var already exist

// int add_new_env(t_com_export *head, char *env)
// {

// } 

// t_com_export *find_env_var(t_com_export *head, char *env)
// {


// }

t_env *find_last_node(t_env *head)
{
    t_env *last_node;
    last_node = head;
    while (last_node->next != NULL)
    {
        last_node = last_node->next;
    }
    return(last_node);
}

void add_env_node(t_env **head, char *env)
{
    t_env *new_env;
    t_env *last_env;
    char **splited_env_var;

    splited_env_var = ft_split(env, '=');
    new_env = malloc(sizeof(t_env));
    if(new_env == NULL)
        return exit(1);
    new_env->next = NULL;
    new_env->key = splited_env_var[0];
    new_env->value = splited_env_var[1];

    if(*head == NULL)
    {
        *head = new_env;
        return ;
    }

    last_env = find_last_node(*head);
    last_env->next = new_env;
}

void *set_my_env(char **environ, t_env **head)
{
    int i;

    i = 0;
    while(environ[i])
    {
        add_env_node(head, environ[i]);
        i++;
    }


    

    return (0);
}




int main()
{
    extern char **environ;
    t_env *my_env;

    my_env = NULL;
    set_my_env(environ, &my_env);

    t_env *current = my_env;
    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    return 0;
}
