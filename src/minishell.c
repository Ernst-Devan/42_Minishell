
#include "minishell.h"
#include "env_manage.h"
#include "libft.h"
#include "exec.h"
#include "parsing.h"

int	minishell(char **env)
{
	t_table table;
	t_shell shell;
	int		val_return;
	char	**ms_env;

	ms_env = new_env(env);
	if (!ms_env)
		return(1);
	shell.error_code = 0;
	while (1)
    {
		shell.env = ms_env;
		table = parsing(&shell);
		display_table(table);
		if (shell.error_code == 0)
			shell = exec(table, &ms_env, shell);
		// REFAIRE LA GESTION D'ERREUR EN DESSOUS
		// if (shell.error_code == ???)
		// {
		// 	// fonction qui free tout
		// 	return (1);
		// }
    }
	// ici aussi il faut tout free
	return (0);
}

int main(int ac, char **argv, char **env) {
  (void)ac;
  (void)argv;
  if (minishell(env))
    return (1);
  return (0);
}
