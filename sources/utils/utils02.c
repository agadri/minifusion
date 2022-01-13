#include "../../includes/minishell.h"

int is_dollar(char *s)
{
	int i;
	int len;

	len = 0;
	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			if (s[i] == '\"')
			{
				i++;
				while (s[i] != '\"')
					i++;
				if (s[i] == '\"')
					i++;
			}
			if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					i++;
				if (s[i] == '\'')
					i++;
			}
			if (s[i] == '$')
				return (1);
			i++;
		}
	}
	return (0);
}

int is_dollar_2(char *s)
{
	int i;
	int len;

	len = 0;
	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			if (s[i] == '\"')
			{
				i++;
				while (s[i] != '\"')
				{
					if (s[i] == '$')
						return (1);
					i++;
				}
				if (s[i] == '\"')
					i++;
			}
			i++;
		}
	}
	return (0);
}

char	*ft_join(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc(len1 + len2 + 1);
	i = -1;
	while (++i < len1)
		new[i] = s1[i];
	j = 0;
	while (i < len1 + len2)
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
char *remove_dollar(char *str, int index)
{
	int		i;
	int 	j;
	int 	temp;
	int		len;
	char 	*path;
	char 	*dest;
	char	*tmp;

	len = 0;
	temp = index + 1;
	j = index;
	i = 0;
	len += ft_strlen(str);
	while (str[index] && (str[index] != ' ' && str[index] != '\'' && str[index] != '\"' && !is_dollar_sep(str[index])))
	{
		index++;
		i++;
	}
	path = (char *)malloc(sizeof(char) * (i));
	if (!path)
		return (NULL);
	len -= i;
	i = 0;
	while (str[temp] && (str[temp] != ' ' && str[temp] != '\'' && str[temp] != '\"' && !is_dollar_sep(str[temp])))
	{
		path[i] = str[temp];
		temp++;
		i++;
	}
	path[i] = '\0';
	tmp = getenv(path);
	len += ft_strlen(tmp);
	i = 0;
	temp = 0;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	if (!dest)
		return (NULL);
	while (len < ft_strlen(str))
	{
		if (i == j)
		{
			if (tmp)
			{
				while (tmp[temp])
				{
					dest[i] = tmp[temp];
					i++;
					temp++;
				}
				len += ft_strlen(path) + 1;
			}
			else
				len += ft_strlen(path) + 1;
		}
		else 
		{
			dest[i] = str[len];
			i++;
			len++;
		}
	}
	dest[i] = '\0';
	free (path);
	free (str);
	return (dest);
}

char *treat_dollar(char *str)
{
	int 	i;
	char	*dest;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			if (str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '$')
		{
			dest = remove_dollar(str, i);
			return (dest);
		}
		else
			i++;
	}
	return (str);
}

char *treat_dollar_in_dquote(char *str)
{
	int 	i;
	char	*dest;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					dest = remove_dollar(str, i);
					return (dest);
				}
				i++;
			}
			if (str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
		}
		i++;
	}
	return (str);
}