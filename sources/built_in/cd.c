#include "../../includes/minishell.h"


/* ==== CD === */

void	built_in_cd(t_env *env, t_lexer *lexer, char *path)//chdir?? man
{
	(void)lexer;
	env->oldpwd = ft_strdup(env->pwd);
	if (!path && env->home)
	{
		chdir(env->home);
	}
	else if (!ft_strcmp(path, "-"))
		chdir("..");
	else if (chdir(path) == -1)//chdir permet de redefinir le chemin si path == ".." le chemin rendu recule
		printf("chdir()\n	");
	//changer  le pwd (prend le chdir() et le old pwd(prend le pwd) de env swan t bo
}

