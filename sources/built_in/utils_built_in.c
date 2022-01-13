#include "../../includes/minishell.h"

int		ft_atoi(char *str)
{
	int neg;
	int i;
	int num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

char	*ft_argsdup(char *str)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!str)
		return (NULL);
	while (str[len] && str[len] != '=')
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_valdup(char *str)
{
	char	*dup;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (str[len] && str[len] != '=')
	{	
		len++;
		j++;
	}
	len++;
	j++;
	while (str[len])
	{		

		len++;
		i++;
	}
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (str[j])
	{
		dup[i] = str[j];
		i++;
		j++;
	}
	dup[i] = '\0';
	return (dup);
}
