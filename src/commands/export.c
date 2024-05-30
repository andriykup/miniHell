/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconvent <aconvent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:30:53 by ankupins          #+#    #+#             */
/*   Updated: 2024/05/30 15:08:02 by aconvent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ****************
// TO FIX:
//  export 123= -> assigns value null instead of empty!





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

// -- utils for my_env_to_arr(t_env *head) 

static int	ft_length_custom(char const *s1, char const *s2)
{
	int	i;
	int	ret;
	i = 0;
	ret = 0;
    if(s2 != NULL)
    {
        while (s1[i])
        {
            i++;
            ret++;
        }
    }
	i = 0;
    if(s2 != NULL)
    {
        while (s2[i])
        {
            i++;
            ret++;
        }
    }
	return (ret);
}


///



int linked_list_length(t_env *head)
{
    t_env *current = head;
    int i = 0;

    while(current != NULL)
    {
        i++;
        current = current->next;
    }

    return (i);
}

// take linked list where each node is env var, copy it to 2d arr to use in execve
// char **my_env_to_arr(t_env *head) 
// {
//     char **my_env_arr;
//     t_env *current = head;
//     int arr_i = 0;
//     int y;
//     int u;


//     my_env_arr = malloc((linked_list_length(head) + 1) * sizeof(char *));

//     while (current) 
//     {
//         my_env_arr[arr_i] = malloc(sizeof(char *) * (ft_length_custom(current->key, current->value) + 2));
//         if(my_env_arr == NULL)
//             return NULL;
//         y = 0;
//         if(current->key != NULL)
//         {
//             while(current->key[y])
//             {
//                 my_env_arr[arr_i][y] = current->key[y];
//                 y++;
//             }
//             my_env_arr[arr_i][y++] = '=';
//         }
//         u = 0;
//         if(current->value == NULL)
//             y++;
//         else
//         {
//             while(current->value[u])
//             {
//                 my_env_arr[arr_i][y] = current->value[u];
//                 y++;
//                 u++;
//             }
//         }
//         my_env_arr[arr_i][y] = '\0';
//         current = current->next;
//         arr_i++;
//     }
//     my_env_arr[arr_i] = NULL;
//     return (my_env_arr);
// }

char	*ft_strdup(const char *s)
{
	char	*pnt;
	int		i;
    if(s == NULL)
        return NULL;
	i = 0;
	while (s[i])
		i++;
	pnt = (char *)malloc((i + 1) * sizeof(char));
	if (!pnt)
		return (NULL);
	i = 0;
	while (s[i])
	{
		pnt[i] = s[i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
}

//utils !!!!!!!!!!!!


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
        {
            ft_free_2arr(splited_env_var);
            return (current);
        }
        current = current->next;
    }
    ft_free_2arr(splited_env_var);
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
    new_env->key = ft_strdup(splited_env_var[0]); // what if the malloc fails
    new_env->value = ft_strdup(splited_env_var[1]);// what if the malloc fails

    int i = 0;
    while(splited_env_var[i])
    {
        free(splited_env_var[i]);
        i++;
    }
    free(splited_env_var);

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

void free_my_env(t_env *head)
{
    if(head == NULL)
        return ;
    t_env *current = head;
    t_env *next;
    while(current)
    {
        free(current->key);
        free(current->value);
        next = current->next;
        free(current);
        current = next;
    }
}

// int main()
// {
//     extern char **environ;
//     t_env *my_env;
//     char **my_env_arr;

//     my_env = NULL;
//     set_my_env(environ, &my_env); // copy env var
//     // com_export(my_env, "123=456"); //export works :)
//     // com_export(my_env, "ABC=ZXC"); //export test :)
//     // com_export(my_env, "ABC=Andriy"); //export test in case ENV already exist :)
//     // com_export(my_env, "123=123"); //export test in case ENV already exist :)

//     // com_env(my_env);
//     // printf("---\n\n");
//     // com_unset(&my_env, "123");  //unset works :)
//     // com_unset(&my_env, "ABC1"); //unset works :)
//     // printf("---\n\n");

//     //com_env(my_env); // print linked list env

//     //my_env_arr = my_env_to_arr(my_env);
//     my_env_arr = my_env_to_arr(my_env);

//     // --- check ->  t_env *my_env;
//     //com_env(my_env);

//     // --- check ->  char **my_env_arr;
//     // int i = 0;
//     // while(my_env_arr[i])
//     // {
//     //     printf("%s\n", my_env_arr[i]);
//     //     i++;
//     // }
//     free_my_env(my_env, my_env_arr);
//     // !!!!!!!!!!!   create function to free *my_env AND **my_env_arr   !!!!!!!!!!!!!!!
//     return 0;
// }
