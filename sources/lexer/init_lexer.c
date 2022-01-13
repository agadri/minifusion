#include "../../includes/minishell.h"

void		define_token_type(t_command *command, int n_token)
{
	int i;

	i = 0;
	while (i < n_token)
	{
		if (i != 0)
		{
			if (command->token[i].data[0] != '>' && command->token[i].data[0] != '<' && command->token[i - 1].type == FILE_OUT_SUR)
				command->token[i].type = EXIT_FILE_RET;
			else if(command->token[i].data[0] != '>' && command->token[i].data[0] != '<' && command->token[i - 1].type == HERE_DOC)
				command->token[i].type = LIMITOR;
			else if(command->token[i].data[0] != '>' && command->token[i].data[0] != '<' && command->token[i - 1].type == FILE_IN)
				command->token[i].type = OPEN_FILE;
			else if(command->token[i].data[0] != '>' && command->token[i].data[0] != '<' && command->token[i - 1].type == FILE_OUT)
				command->token[i].type = EXIT_FILE;
			else if (command->token[i - 1].type == ARG ||
				command->token[i - 1].type == EXIT_FILE_RET ||
				command->token[i - 1].type == LIMITOR ||
				command->token[i - 1].type == OPEN_FILE ||
				command->token[i - 1].type == EXIT_FILE)
				command->token[i].type = ARG;
		}
		if (command->token[i].data[0] == '>' && command->token[i].data[1] == '>')
				command->token[i].type = FILE_OUT_SUR;
		else if (command->token[i].data[0] == '<' && command->token[i].data[1] == '<')
					command->token[i].type = HERE_DOC;
		else if (command->token[i].data[0] == '<' && command->token[i].data[1] == '\0')
					command->token[i].type = FILE_IN;
		else if (command->token[i].data[0] == '>' && command->token[i].data[1] == '\0')
					command->token[i].type = FILE_OUT;
		else if (i == 0)
			command->token[i].type = ARG;
		i++;
	}
}

void		get_args(t_command *command)
{
	int i;
	int n_args;

	i = 0;
	n_args = 0;
	while (i < command->n_token)
	{
		if (command->token[i].type == ARG)
			n_args++;
		i++;
	}
	command->args = (char **)malloc(sizeof(char *) * (n_args + 1));
	if (!command->args)
		return ;
	i = 0;
	n_args = 0;
		while (i < command->n_token)
	{
		if (command->token[i].type == ARG)
		{
			command->args[n_args] = ft_strdup(command->token[i].data);
			n_args++;
		}
		i++;
	}
	command->args[n_args] = 0;
}

void		init_token(char *str, t_command *commands)
{
	char **strs;
	int i;

	i = 0;
	strs = ft_split(str, ' ');
	while (strs[i])
		i++;
	commands->n_token = i;
	commands->token = (t_token *)malloc(sizeof(t_token) * i);
	if (!commands->token)
		return ;
	i = 0;
	while (strs[i])
	{
		commands->token[i].data = ft_strdup(strs[i]);
		commands->token[i].data_len = ft_strlen(commands->token[i].data);
		free (strs[i]);
		i++;
	}
	define_token_type(commands, commands->n_token);
	free (strs);
}

t_command	*init_command_struct(char **str, t_lexer *lexer)
{
	t_command	*commands;
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	lexer->n_command = i ;
	commands = (t_command *)malloc(sizeof(t_command) * i);
	i = 0;
	while (str[i])
	{
		commands[i].command = remove_space(str[i]);
		init_token(str[i], &commands[i]);
		remove_all_dollar_from_command(&commands[i]);
		remove_all_quote_from_command(&commands[i]);
		get_args(&commands[i]);
		i++;
	}
	return (commands);
}


t_lexer	*init_lexer(char **str)
{
	t_lexer *lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->command = init_command_struct(str, lexer);
	return (lexer);
}

