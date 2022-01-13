#include "../../includes/minishell.h"

char *ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	built_in_export(t_env *env, t_lexer *lexer, char *var)
{
	int	i;
	//int	size;
	t_tab	**tab;

	(void)lexer;
	//size = 0;
	//while (env->tab[size])
	//	size++; 
	env->tab_size += 1;
	tab = malloc(sizeof(t_tab *) * (env->tab_size + 1));
	if (!tab)
		return ;
	i = 0;
	while (env->tab[i])
	{
		tab[i] = malloc(sizeof(t_tab) * 1);
		if (!tab[i])
			return ;
		tab[i]->args = ft_strdup(env->tab[i]->args);
		tab[i]->val = ft_strdup(env->tab[i]->val);
		i++;
	}
	tab[i] = malloc(sizeof(t_tab) * 1);//args et val
	tab[i + 1] = malloc(sizeof(t_tab) * 1);//'\0'
	if (!tab[i] || !tab[i + 1])
		return ;
	tab[i]->args = ft_argsdup(var);//la je copie la nouvelle variable 
	tab[i]->val = ft_valdup(var);//pareil
	tab[i + 1]->args = NULL;
	tab[i + 1]->val = NULL;
	i = 0;
	while (env->tab[i])//free l'ancien tab
	{
		free(env->tab[i]);
		env->tab[i] = NULL;//NULL et free sur l'ancien tab
		i++;
	}
	env->tab = NULL;
	free(env->tab);
	env->tab = malloc(sizeof(t_tab *) * (env->tab_size + 1));// je le remalloc
	if (!env->tab)
		return ;
	env->tab[env->tab_size] = NULL;
	i = 0;
	while (tab[i]->args != NULL)// et recopie dedans bam;
	{
		env->tab[i] = malloc(sizeof(t_tab) * 1);
		if (!env->tab[i])
			return ;
		env->tab[i]->args = ft_strdup(tab[i]->args);
		env->tab[i]->val = ft_strdup(tab[i]->val);
		i++;
	}
}