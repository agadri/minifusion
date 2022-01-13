#include "../../includes/minishell.h"

void	make_redirection(t_command *command, int (*fd)[2048][2], int fd_index)
{
	int i = 0;

	while (i < command->n_token)
	{
		if (command->token[i].type == FILE_OUT)
		{
			(*fd)[fd_index + 1][1] = open(command->token[i + 1].data, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if ((*fd)[fd_index + 1][1] < 0)
				return ;
		}
		else if(command->token[i].type == FILE_OUT_SUR)
		{
			(*fd)[fd_index + 1][1] = open(command->token[i + 1].data, O_RDWR | O_CREAT | O_APPEND, 0644);
			if ((*fd)[fd_index + 1][1] < 0)
				return ;
		}
		else if (command->token[i].type == FILE_IN)
		{
			(*fd)[fd_index][0] = open(command->token[i + 1].data, O_RDONLY);
			if ((*fd)[fd_index][0] < 0)
				return ;
		}
		else if (command->token[i].type == HERE_DOC)
			here_doc(command->token[i + 1].data, fd, fd_index);
		i++;
	}
}

void	ft_putstr_fd(char *str, int fd);

int	treat_redirection(t_lexer *lexer, int (*fd)[2048][2], int fd_index, int n_command)
{
	t_command	*command;
	int i = 0;
 	int ret_1;
	int ret_2;
	
	ret_1 = 0;
	ret_2 = 0;
	command = &lexer->command[fd_index];
	while (i < command->n_token)
	{
		if (command->token[i].type == FILE_OUT || command->token[i].type == FILE_OUT_SUR)
		{
			ret_1 = 1;
			dup2((*fd)[fd_index + 1][1], STDOUT_FILENO);
		}
		else if (command->token[i].type == FILE_IN || command->token[i].type == HERE_DOC)
		{
			ret_2 = 1;
			dup2((*fd)[fd_index][0], STDIN_FILENO);
		}
		i++;
	}
	if (fd_index + 1 < n_command && !ret_1)
		dup2((*fd)[fd_index + 1][1], STDOUT_FILENO);
	if (fd_index > 0 && !ret_2)
		dup2((*fd)[fd_index][0], STDIN_FILENO);
	if (!ret_1 && (fd_index < n_command - 1) && has_heredoc(&lexer->command[fd_index + 1]) )
		return (1);
	return (0);
}

void    here_doc(char *eof, int (*fd)[2048][2], int i)
{
    char	*line;
	char	*var;
	char	*no_dollar;
    int		len;
	int		ret;

	ret = has_quote(eof);
	if (ret)
	{
		free (eof);
		eof = remove_quote_from_limitor(eof);
	}
    line = readline("> ");
	len = 0;
    while (ft_strcmp(line, eof) != 0)
    {
		if (line[0] == '$' && ret == 0)
		{
			no_dollar = remove_dollar_from_string(line);
			var = getenv(no_dollar);
			len = ft_strlen(var);
			write((*fd)[i][1], var, len);
			write((*fd)[i][1], "\n", 1);
			free(no_dollar);
			free(line);
		}
		else
		{
			len = ft_strlen(line);
			write((*fd)[i][1], line, len);
			write((*fd)[i][1], "\n", 1);
			free(line);
		}

		line = readline("> ");
    }
    free(line);
}

int	has_heredoc(t_command *command)
{
	int i;

	i = 0;
	while (i < command->n_token)
	{
		if (command->token[i].type == HERE_DOC)
			return (1);
		i++;
	}
	return (0);
}