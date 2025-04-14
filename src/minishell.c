
#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "libft.h"

int	minishell(char **env)
{
	t_table table;

	while (1)
    {
		table = parsing(env);
		if(exec(table, env))
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

