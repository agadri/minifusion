#include "../../includes/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_charspe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
		{
			printf("%s\n","bash: syntax error near unexpected token '<'");
			return (1);
		}
		else if (str[i] == '>' && str[i + 1] != '>')
		{
			printf("%s\n","bash: syntax error near unexpected token '>'");
			return (1);
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			printf("%s\n","bash: syntax error near unexpected token '<<'");
			return (1);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			printf("%s\n","bash: syntax error near unexpected token '>>'");
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] != '/')
		{
			printf("%s\n","bash: syntax error near unexpected token '<'");
			return (1);
		}
		else if (str[i] == '>' && str[i + 1] != '>')
		{
			printf("%s\n","bash: syntax error near unexpected token '>'");
			return (1);
		}
		i++;
	}
	return (0);
}

void	built_in_exit(t_lexer *lexer, t_env *env, int i)
{
	//1
	//exit sans rien quit
	(void)env;
	printf("ii %d\n", i);
	if (i >= 2)
		printf("bash: exit: too many arguments\n");
	else if (lexer->command[i].token[0].data && !lexer->command[i].token[1].data)
		exit(EXIT_SUCCESS);
	else if (lexer->command[i].token[0].data && lexer->command[i].token[1].data)
	{
		int	nbr;
		if (is_charspe(lexer->command[i].token[1].data))
			printf("ah\n");
		else if (is_slash(lexer->command[i].token[1].data))
			printf("eh\n");
		else if (!is_num(lexer->command[i].token[1].data))// si ya que des chiffres 
		{
			nbr = ft_atoi(lexer->command[i].token[1].data);//convertie en int ;
			//free_lexer(lexer);
			//free_env(env);
			exit(nbr);//exit avec l'int;
		}
		else
			printf("exit: %s : numeric argument required\n", lexer->command[i].token[1].data);//sinon c'est tchao
	}
	else if(!lexer->command[i].token[1].data)
	{
		//free_lexer(lexer);
		//free_env(env);
		exit(EXIT_SUCCESS);
	}

	//2
	//exit exit ->bash: exit: hola: numeric argument required
	//3
	//exit "blabla" bash: exit: hola: numeric argument required
	//4
	//exit 'nombre' exit normal
	//5
	//exit 'nbr' ' nbr' ->bash: exit: hola: numeric argument required
	//6
	// exit 'nbr ' * etc -> pareil

}