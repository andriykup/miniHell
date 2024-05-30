#include "../../include/mini_hell.h"


t_redir *redir_init() {
    t_redir *new_redir;
    new_redir = malloc(sizeof(t_redir));
    if (new_redir == NULL) {
        // error management
        return NULL;
    }
    new_redir->file_name = NULL;
    new_redir->redir = NULL;
    new_redir->next = NULL;
    return new_redir;
}

t_command* init_command() {
    t_command *new_command;
    new_command = (t_command*)malloc(sizeof(t_command));
    if (new_command == NULL) {
        return NULL;
    }
    new_command->redir = NULL;
    new_command->redirected = false;
    new_command->next = NULL;
    return new_command;
}

void skip_quotes(char *str, int *i) {
    char quote;
    quote = str[*i];
    (*i)++;
    while (str[*i] != quote && str[*i] != '\0') {
        (*i)++;
    }
}

bool is_quotes(char c) {
    return (c == '\'' || c == '\"');
}

bool token_delimiter(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '<' || c == '>');
}

char *tokenizing(char *input, int *i) {
    int saved;
    char *res;

    saved = *i;
    while (input[*i] && !token_delimiter(input[*i])) 
    {
        if (is_quotes(input[*i]))
            skip_quotes(input, i);
        else
            (*i)++;
    }
    res = ft_substr(input, saved, *i - saved);
    if (!res) 
    {
        // error management
    }
    return res;
}

void skip_spaces(char *str, int *i) {
    while (str[*i] == ' ' || str[*i] == '\t' ||str[*i] == '\n') {
        (*i)++;
    }
}

t_redir *get_redir(char *str, int *i) 
{
    t_redir *redi;
    int j;

    j = 0;
    redi = redir_init();
    if (str[*i] == '<')
        redi->redir = strdup("<");
    else if (str[*i] == '>') {
        if (str[*i + 1] == '>')
        {
            redi->redir = strdup(">>");
            (*i)++;
        } 
        else
            redi->redir = strdup(">");
    }
    (*i)++;
    skip_spaces(str, i);
    redi->file_name = tokenizing(str, i);
    return redi;
}

void get_command(char *input, t_command **cmd) {
    int j = 0;
    int i = 0;
    t_redir *redir;

    if (!cmd) {
        exit(1);
    }
    (*cmd)->args = malloc(sizeof(char *) + 10); // Allocate space for args
    if (!(*cmd)->args) {
        // error management
        return;
    }
    while (input[i]) 
    {
        skip_spaces(input, &i);
        if (input[i] != '<' && input[i] != '>') {
            (*cmd)->args[j] = tokenizing(input, &i);
            j++;
        } else if (input[i] == '<' || input[i] == '>') {
            (*cmd)->redirected = true;
            redir = get_redir(input, &i);
            add_redir_to_end(&(*cmd)->redir, redir);
        }
        skip_spaces(input, &i);
    }
    (*cmd)->args[j] = NULL;
}

void add_command_to_end(t_command **head, t_command *new_node) {
    t_command *current;

    if (head == NULL || new_node == NULL)
        return;
    if (*head == NULL)
        *head = new_node;
    else 
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void add_redir_to_end(t_redir **head, t_redir *new_node) {
    t_redir *current;
    if (head == NULL || new_node == NULL)
        return;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current = *head;
        while (current->next != NULL) 
            current = current->next;
        current->next = new_node;
    }
}

t_command *command_list(t_mini_shell mini_shell) 
{
    t_command *cmd_head;
    t_command *cmd;
    int i = 0;

    cmd_head = NULL;
    while (mini_shell.parsed_input[i] != NULL) 
    {
        cmd = init_command();
        if (cmd == NULL)
            return NULL;
        get_command(mini_shell.parsed_input[i], &cmd);
        add_command_to_end(&cmd_head, cmd);
        i++;
    }
   print_command_list(cmd_head);
    return cmd_head;
}

void print_redir(t_redir *redir) {
    while (redir != NULL) {
        printf("  Redirection: %s %s\n", redir->redir, redir->file_name);
        redir = redir->next;
    }
}

// Function to print command list
void print_command_list(t_command *cmd) {
    while (cmd != NULL) {
        printf("Command:\n");
        if (cmd->args == NULL)
            printf("the args is NULL");
        if (cmd->args != NULL) {
            for (int i = 0; cmd->args[i] != NULL; i++) {
                printf("  Arg[%d]: %s\n", i, cmd->args[i]);
            }
        }
        printf("  Redirected: %s\n", cmd->redirected ? "true" : "false");
        if (cmd->redir != NULL) {
            print_redir(cmd->redir);
        }
        if (cmd->next != NULL)
            printf("---------new command----------\n");
        cmd = cmd->next;
    }
}