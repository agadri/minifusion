#include "../../includes/minishell.h"

// regroupe les commandes 

int	is_built_in(char *cmd)//je guete sur quelle commade je tombe 
{
	char	*tab[] = {"echo", "cd", "pwd", "export", "unset", "env","exit", NULL};
	int	i;

	i = 0;
	if (!cmd)
		return (2);
	while (tab[i]) 
	{
		if (!ft_strcmp(tab[i], cmd))//dans le cas ou cela ne correspond a aucun cas ...
			return (1);
		i++;
	}
	return (0);
}

