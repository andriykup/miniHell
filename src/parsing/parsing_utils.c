#include "../../include/mini_hell.h"


typedef struct s_cmds
{
    t_command *cmd;
    struct s_cmd *next;
}   t_cmd;


typedef struct s_command
{
    char *cmd;
	char **args;
    t_redir *redir;
    bool redirected;
} t_command;

typedef struct s_redirection {
    char *file_name;
    char redir[2];
} t_redir;

t_command* init_command() 
{
    t_command *new_commands;

    new_commands = (t_command*)malloc(sizeof(t_command));
    if (new_commands == NULL)
        return NULL;
    new_commands->cmd = NULL;
    new_commands->args = NULL;
    new_commands->redir = NULL;
    new_commands->redirected = false; 
    return new_commands;
}

char *tokenizing(char *input, int *i)
{
    int  saved;
    char *res;

    saved = (*i);
    while (input[(*i)] && !token_delimiter(input[(*i)]))
    {
        if (is_quotes(input[*i]))
            skip_quotes(input[*i]);
        else 
            (*i)++;
    }
    res = ft_substr(input, saved, i - saved );
    if (!res)
    {
        //error management
    }
    return (res);
}
t_command *get_command(char *input)
{
    int i;
    t_command *cmd;
    t_redir *redir;

    i = 0;
    int j;
    cmd = init_command(cmd);
    if (!cmd)
        exit(1);
    while (input[i])
    {
        if (input[i] != '<' && input[i] != '>')
        {
            if (cmd->cmd == NULL)
                cmd->cmd = tokenizing(input, i);
            else 
                cmd->args[j++] = tokenizing(input, i);
        }
        else if (input[i] == '<' || input[i] == '>')
        {
            cmd->redirected = true;
            cmd->redir = get_redir(input, i);
        }
        skip_spaces(input, i);
    }
    cmd->args[j] = NULL;
    return (cmd);
}

