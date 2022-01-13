#ifndef UTILS_H
#define UTILS_H

char	**ft_split(char *s, char c);
char	*ft_strdup(const char *str);
char    *remove_space(char *str);
char	*ft_cpy(char *s, char c);
int     ft_strlen(char *str);
char	*ft_cpy_quoted(char *s, char c);
char    *add_space_between_redir(char *str);
void    free_double_array(char **array);
char	*ft_join(char *s1, char *s2);
int 	print_error(char *str);
void 	ft_putstr(char *str);
char	*ft_strchr(const char *s, int c);
char	*treat_dollar(char *str);
char 	*treat_dollar_in_dquote(char *str);
char 	*remove_dollar(char *str, int index);
int		is_dollar(char *s);
int		is_dollar_2(char *s);
void	remove_all_dollar_from_command(t_command *command);
void	remove_all_quote_from_command(t_command *command);
char	*remove_all_quote(char *str);
int 	is_dollar_sep(char c);
int		ft_strcmp(char *s1, char *s2);
char	*remove_quote_from_limitor(char *limitor);
int		has_quote(char *limitor);
char	*remove_dollar_from_string(char *string);

#endif