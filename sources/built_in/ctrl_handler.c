#include "../../includes/minishell.h"
/*
int	wait_free(t_lexer *lexer, t_env *env)
{
	pid_t	pid = 0;
	pid = fork();
	if (pid < 0)
	{
		printf("oh no\n");
		free_command(lexer->command);
		free_lexer(lexer);
		exit(1);
	}
	if (pid == 0)
	{
		pause();
		printf("hey\n");
		free_command(lexer->command);
		free_lexer(lexer);
		exit(0);
	}
	return (pid);
}

*/

void	ctrl_c_handler(int	sig)
{
	(void)sig;
	printf("CCCCCC\n");
	exit(0);
}

void	ctrl_d_handler(int	sig)
{
	(void)sig;
	printf("ZZZZZZZ\n");
	exit(0);
}

void	ctrl_s_handler(int	sig)
{
	(void)sig;
	printf("///////\n");
	exit(0);
}