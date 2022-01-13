#include "../../includes/minishell.h"

void clean(char **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
	}
	tab = NULL;
}

int	ft_count_word(char const *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			word++;
			while (*s && *s != c)
				s++;
		}
	}
	return (word);
}

char	*ft_cpy(char *s, char c)
{
	char	*dest;
	int		i;

	i = 0;
	while (i < ft_strlen(s) && s[i] != c)
	{	
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			if (s[i] == '\"')
				i++;
		}
		else
			i++;
	}
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'')
		{
			dest[i] = s[i];
			i++;
			while (s[i] && s[i] != '\'')
			{
				dest[i] = s[i];
				i++;
			}
			if (s[i] == '\'')
			{
				dest[i] = s[i];
				i++;
			}
		}
		else if (s[i] == '\"')
		{
			dest[i] = s[i];
			i++;
			while (s[i] && s[i] != '\"')
			{
				dest[i] = s[i];
				i++;
			}
			if (s[i] == '\"')
			{
				dest[i] = s[i];
				i++;
			}
		}
		else
		{
			dest[i] = s[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	int		i;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			dest[i] = ft_cpy(s, c);
			while (*s && *s != c)
			{
				if (*s == '\'')
				{
					s++;
					while (*s && *s != '\'')
						s++;
					if (*s == '\'')
						s++;
				}
				else if (*s == '\"')
				{
					s++;
					while (*s && *s != '\"')
						s++;
					if (*s == '\"')
						s++;
				}
				else
					s++;
			}
			if (dest[i] == NULL)
				clean(dest, i);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
//	printf("i : %d\n", i);
	dest[i] = NULL;
	return (dest);
}
