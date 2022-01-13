#include "../../includes/minishell.h"

//unset supprime une variable et sa valeur dans env

int	built_in_unset(t_env *env, t_lexer *lexer, char *var)
{
	int	i;
	int	j;
	t_tab	**tab;

	i = 0;
	(void)lexer;
	while (env->tab[i])
		i++;
	env->tab_size = i - 1;//nouvelle taille de tab;
	tab = malloc(sizeof(t_tab *) * (env->tab_size + 1));//malloc tab avec sa nouvelle taille 
	if (!tab)//petite secu des familles
		return (0);
	i = 0;
	j = 0;
	// la je copie et malloc (realloc) dans tab;
	while (env->tab[i])
	{
		tab[j] = malloc(sizeof(t_tab) * 1);
		if (!tab[j])
			return (0);
		if (ft_strcmp(env->tab[i]->args, var))// si dans le tableau il y a la variable on ne la copie pas 
		{
			tab[j]->args = ft_strdup(env->tab[i]->args);
			tab[j]->val = ft_strdup(env->tab[i]->val);
			j++;
		}
		i++;
	}
	i = 0;
	while (env->tab[i])//free l'ancien tab
	{
		free(env->tab[i]->args);
		free(env->tab[i]->val);
		free(env->tab[i]);
		/*env->tab[i]->args = NULL;
		env->tab[i]->val = NULL;
		env->tab[i] = NULL;*///NULL et free sur l'ancien tab
		i++;
	}
	if (env->tab)//free l'ancien tab
	{
		env->tab = NULL;
		free(env->tab);
	}
	env->tab = malloc(sizeof(char *) * (env->tab_size + 1));// je le remalloc
	if (!env->tab)
		return (0);
	env->tab[env->tab_size] = NULL;
	i = 0;
	j = 0;
	while (i < env->tab_size)// et recopie dedans bam;
	{
		env->tab[j] = malloc(sizeof(t_tab) * 1);
		if (!env->tab[j])
			return (0);
		printf("compare[%d] ->%s\n", i,tab[i]->args);
		env->tab[j]->args = ft_strdup(tab[i]->args);
		env->tab[j]->val = ft_strdup(tab[i]->val);
		i++;
		j++;
	}
	return (1);
}