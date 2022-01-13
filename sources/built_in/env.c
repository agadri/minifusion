#include "../../includes/minishell.h"

//env affiche l'environnement donc le copie le tableau 
// pour pouvoir y avoir acces plus tars et je l'affiche ..
//SHLVL

int	sizetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	take_and_cpy_env(t_env *envi, char **env, t_lexer *lexer)
{
	int	size;
	int	i;
	(void)lexer;
	if (!env)
		return (0);
	if (envi->state == 1)
		return (0);
	//if (lexer->state_of_init == 1)
	//	return (0);
	size = sizetab(env);
	envi->tab_size = size;
	envi->tab = malloc(sizeof(t_tab *) * (size + 1));
	if (!envi->tab)
		return (0);
	i = 0;
	while (i < size)
	{
		envi->tab[i] = malloc(sizeof(t_tab));
		if (!envi->tab[i])
			return (0);
		envi->tab[i]->args = ft_argsdup(env[i]);
		envi->tab[i]->val = ft_valdup(env[i]);
		if (!ft_strcmp(envi->tab[i]->args,"HOME"))
			envi->home = ft_strdup(envi->tab[i]->val);
		else if (!ft_strcmp(envi->tab[i]->args,"OLDPWD"))
			envi->oldpwd = ft_strdup(envi->tab[i]->val);
		i++;
	}
	envi->tab[i] = NULL;
	return (1);
}

void	built_in_env(t_env *env, t_lexer *lexer)//la j'affiche juste l'env
{
	int		i;

	i = 0;
	while (i < env->tab_size)
	{
		if (!ft_strcmp(env->tab[i]->args,"PWD"))//affiche pwd actuel//segfaut askip
		{
			env->pwd = built_in_pwd(env, lexer);
			printf("env[%d] :%s=%s\n", i,env->tab[i]->args, env->pwd);
		}
		else if (!ft_strcmp(env->tab[i]->args,"OLDPWD"))//l'ancien
		{
			printf("env[%d] :%s=%s\n", i, env->tab[i]->args,env->oldpwd);
		}
		else
			printf("env[%d] :%s=%s\n", i,env->tab[i]->args,env->tab[i]->val);
		i++;
	}
}
/*
void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->tab_size)
	{
		if (env->tab[i]->args)
			free (env->tab[i]->args);
		else if (env->tab[i]->val)
			free (env->tab[i]->val);
		else if (env->tab[i])
			free (env->tab[i]);
		i++;
	}
}
*/