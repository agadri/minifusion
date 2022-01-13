#include "includes/minishell.h"

void	receive(int sig, siginfo_t *info, void *envi)
{
	(void)sig, (void)info;
	t_env *env;
	env = (t_env *)envi;
	(void)env;
	printf("i get %d\n", sig);
	if (sig == 2)//si ctr c
	{
		//printf("%s\n" , env->pwd);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	init_tab(t_env **envi)
{
	*envi = malloc(sizeof(t_env));
	if (!*envi)
		return (0);
	(*envi)->tab = NULL;
	(*envi)->pwd = NULL;
	(*envi)->oldpwd = NULL;
	(*envi)->home = NULL;
	(*envi)->tab_size = 0;
	(*envi)->state = 0;
	return (1);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	static t_lexer *lexer = NULL;
	t_env *envi = NULL;
	struct sigaction	sig;
	char **str;
	char *buff;

	if (!init_tab(&envi))
		return (0);
	memset(&sig, 0, sizeof(sig));
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = &receive;
	sigaction(SIGINT, &sig, NULL);//ctrl c raffiche une ligne vide ..
	sigaction(SIGTSTP, &sig, NULL);//ctrl d quit le prgrm
	sigaction(SIGQUIT, &sig, NULL);//ctrl / fait rien 
	while (1)
	{
		buff = readline("Solo_Minishell> ");
		if (!buff)
		{
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (!*buff)
			free(buff);
		else
		{
		//if (!check_parse_error(buff))
		//{
		// 	free (buff);
		// 	printf("\n");
		// 	continue ;
		// }
			buff = add_space_between_redir(buff);
			add_history(buff);
			str = ft_split(buff, '|');
			lexer = init_lexer(str);
			if (!lexer)
				return (0);
			take_and_cpy_env(envi, env, lexer);
			envi->state = 1;
			printf("state %d\n",envi->state);
			exec_command(envi, lexer, env);
			free(buff);
			free_double_array(str);
			free_lexer(lexer);
			//free_env(envi);
		}
	}
	return (0);
}
