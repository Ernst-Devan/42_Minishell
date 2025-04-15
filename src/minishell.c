
#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "libft.h"
#include "env_manage.h"
#include <stdio.h>

int	minishell(char **env)
{
	t_table table;
	char	**ms_env;

	ms_env = new_env(env);
	if (!ms_env)
		return(1);
	while (1)
    {
		print_env(ms_env);
		table = parsing(ms_env);
		if (exec(table, &ms_env))
		{
			// fonction qui free tout
			return (1);
		}
    }
	// ici aussi il faut tout free
	return (0);
}

int main(int ac, char **argv, char **env)
{
    (void)ac;
    (void)argv;
	if (minishell(env))
		return (1);
	return (0);
}

