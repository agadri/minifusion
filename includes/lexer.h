#ifndef LEXER_H
#define LEXER_H

#define NONE 0
#define ARG 1
#define FILE_IN 2 //word == '<'
#define HERE_DOC 3 // word == '<<'
#define FILE_OUT 4 //word == '>'
#define FILE_OUT_SUR 5 //word == '>>'
#define OPEN_FILE 6 // word following '<'
#define LIMITOR 7 // word following '<<'
#define EXIT_FILE 8 // word following '>'
#define EXIT_FILE_RET 9 // word following '>>'

typedef struct s_norme
{
	int	i;
	int j;
	int temp;
}	t_norme;

typedef struct s_tab
{
	char	*args;
	char	*val;
}	t_tab;

typedef struct  s_token
{
    char        	*data;
	int 			data_len;
    int        		type;
}   t_token;

typedef struct  s_command
{
	char			*command;
    struct s_token	*token;
	char 			**args;
	int				n_token;
	char			*path;	
}   t_command;


typedef struct s_lexer
{
	t_command		*command;
	int				n_command;
}   t_lexer;

typedef struct  s_env
{
	int				state;
	t_tab			**tab;
	char			*pwd;
	char			*oldpwd;
	char			*home;
	int				tab_size;

}	t_env;

t_lexer		*init_lexer(char **str);
t_command	*init_command_struct(char **str, t_lexer *lexer);
void		get_args(t_command *command);
void		init_token(char *str, t_command *commands);
void		define_token_type(t_command *commands, int n_token);
void		make_redirection(t_command *command, int (*fd)[2048][2], int fd_index);
int			treat_redirection(t_lexer *lexer, int (*fd)[2048][2], int fd_index, int n_command);
void		treat_here_doc(t_lexer *lexer, int (*fd)[2048][2]);
int			has_heredoc(t_command *command);
void    	here_doc(char *eof, int (*fd)[2048][2], int i);
void		close_fds(int (*fd)[2048][2], int n_command);

#endif