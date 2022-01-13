#include "../../includes/minishell.h"

/* ==== PWD === */

//getcwd permet de recuperer le chemin du fichier donne donc exactement se pwd fait

char	*built_in_pwd(t_env *env, t_lexer *lexer)
{
	char cwd[256];
	(void)lexer;
	if (getcwd(cwd, sizeof(cwd)) != NULL)//petite secu
	{
		//printf("%s", cwd);//pouf on affiche le chemin incroyable
		env->pwd = ft_strdup(cwd);
	}
	return (env->pwd);
	//else
		//il me semble qu'il affiche rien si pas de chemin ...a verifier
}

void	printf_pwd(t_env *env, t_lexer *lexer)
{
	//char cwd[256];
	(void)lexer;
	built_in_pwd(env, lexer);
	printf("%s\n", env->pwd);//pouf on affiche le chemin incroyable
	//env->pwd = ft_strdup(cwd);
	//return (env->pwd);
}