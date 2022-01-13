#include "../../includes/minishell.h"

void    free_token(t_token *token)
{
    if (token->data)
        free (token->data);
}

void    free_command(t_command *command)
{
    int i;

    i = 0;
    while (command && i < command->n_token)
    {
        if (&command->token[i])
            free_token(&command->token[i]);
        i++;
    }
    if (command && command->command)
        free (command->command);
    if (command && command->token)
        free (command->token);
    if (command && command->args)
        free_double_array(command->args);
    if (command->path)
        free(command->path);
}

void    free_lexer(t_lexer *lexer)
{
    int i;

    i = 0;
    while (i < lexer->n_command)
    {
        free_command(&lexer->command[i]);
        i++;
    }
    free (lexer->command);
    free (lexer);
}
