#include "../../includes/minishell.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (0);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    if (str)
        while (str[i])
            i++;
    return (i);
}

char   *remove_space(char *str)
{
    int     i;
    int     j;
    int     len;
    char    *dest;

    len = ft_strlen(str);
    if (str[len - 1] == ' ')
        len--;
    if (str[0] == ' ')
        len--;
    dest = (char *)malloc(len + 1);
    if (!dest)
        return (NULL);
    i = 0;
    if (str[0] == ' ')
        i++;
    j = 0;
    while (j < len)
    {
        if (str[i] == ' ' && i == len - 1)
            break ;
        dest[j] = str[i];
        j++;
        i++;
    }
    dest[j] = '\0';
    return (dest);
}

char	*add_space_between_redir(char *str)
{
    int     len;
    char    *dest;
    int     i;
	int		j;

    i = 0;
	j = 0;
    len = ft_strlen(str);
    while (i < ft_strlen(str))
    {
        if ((str[i] != '>' && str[i] != '<')
            && (str[i + 1] == '>' || str[i + 1] == '<'))
            len++;
        else if ((str[i] == '>' || str[i] == '<') && (str[i + 1] != '>'
            && str[i + 1] != '<' && str[i + 1] != ' '))
            len++;
        i++;
    }
	i = 0;
    dest = (char *)malloc(sizeof(char) * (len + 1));
    if (!dest)
    {
        return (NULL);
    }
	while (i < ft_strlen(str))
	{
        if ((str[i] != '>' && str[i] != '<') && (str[i + 1] == '>' || str[i + 1] == '<'))
        {
			dest[j] = str[i];
			j++;
			dest[j] = ' ';
		}
        else if ((str[i] == '>' || str[i] == '<') && (str[i + 1] != '>'
            && str[i + 1] != '<' && str[i + 1] != ' '))
			{
				dest[j] = str[i];
				j++;
				dest[j] = ' ';
			}
		else
			dest[j] = str[i];
		i++;
		j++;
	}
    free (str);
	dest[j] = '\0';
	return (dest);
}

void    free_double_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        if (array[i])
            free(array[i]);
        i++;
    }
    free(array);
}