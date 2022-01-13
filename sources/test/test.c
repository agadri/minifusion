#include "../../includes/minishell.h"

void	print_lexer_struct(t_lexer *lexer)
{
	int i;
	int j;

	i = 0;
	printf("NUMBER OF COMMAND	:		%d\n\n\n", lexer->n_command);
	while (i < lexer->n_command)
	{
		j = 0;
		printf("COMMAND			:		%s\n", lexer->command[i].command);
		printf("NUMBER OF TOKEN		:		%d\n\n", lexer->command[i].n_token);
		while (j < lexer->command[i].n_token)
		{
			printf("TOKEN			:		%s\n", lexer->command[i].token[j].data);
			printf("TYPE			:		%d\n\n", lexer->command[i].token[j].type);
			j++;
		}
		printf("\n\n\n\n");
		i++;
	}
}