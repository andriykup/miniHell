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


////------------------
#include "../../include/mini_hell.h"
void add_env_node(t_env **head, char *env);
t_env *find_env_var(t_env *head, char *env);
void update_env_node(t_env *env_node, char *env);


//// -----------------------------
//int set_my_env(char **environ, t_env *head);


//utils !!!!!!!!!!!!11
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
//utils !!!!!!!!!!!!11





// setenv, putenv, and clearenv  <<<<-----
void com_export(t_env *head, char *new_env_var)
{
    t_env *temp;

    temp = NULL;
    temp = find_env_var(head, new_env_var);
    // check if env already exist
    if(temp == NULL) // env doesnt exist
        add_env_node(&head, new_env_var);
    else            // env exists, will update VALUE
        update_env_node(temp, new_env_var);
}

t_env *find_env_var(t_env *head, char *env)
{
    t_env *current = head;
    char **splited_env_var = ft_split(env, '=');

    while(current != NULL)
    {
        // if KEY exist it will return this node
        if(ft_strncmp(splited_env_var[0], current->key, ft_strlen(splited_env_var[0])) == 0)
            return (current);
        current = current->next;
    }
    return NULL;
}

void update_env_node(t_env *env_node, char *env)
{
    char **splited_env_var = ft_split(env, '=');
    free(env_node->value);
    env_node->value = splited_env_var[1];
}


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
        return exit(1); //need to free memory before exit!!
    new_env->prev = NULL;
    new_env->next = NULL;
    new_env->key = splited_env_var[0];
    new_env->value = splited_env_var[1];

    if(*head == NULL)
    {
        *head = new_env;
        return ;
    }

    last_env = find_last_node(*head);
    if(last_env == NULL)
        new_env->prev = NULL; //working as expected????!
    else
        new_env->prev = last_env; //working as expected????!
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

// need function to free linked list !!!


int main()
{
    extern char **environ;
    t_env *my_env;

    my_env = NULL;
    set_my_env(environ, &my_env); // copy env var
    // com_export(my_env, "123=456"); //export works :)
    // com_export(my_env, "ABC=ZXC"); //export test :)
    // com_export(my_env, "ABC=Andriy"); //export test in case ENV already exist :)
    // com_export(my_env, "123=123"); //export test in case ENV already exist :)

    // com_env(my_env);
    // printf("---\n\n");
    // com_unset(&my_env, "123");  //unset works :)
    // com_unset(&my_env, "ABC1"); //unset works :)
    // printf("---\n\n");

    //com_env(my_env);
    return 0;
}
