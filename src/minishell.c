
#include "minishell.h"
#include "env_manage.h"
#include "libft.h"
#include "exec.h"
#include "parsing.h"

int	minishell(char **env)
{
	t_table table;
	char	**ms_env;
	int		val_return;

	ms_env = new_env(env);
	if (!ms_env)
		return(1);
	while (1)
    {
		table = parsing(ms_env);
		val_return = exec(table, &ms_env);
		if (val_return || val_return == -1)
		{
			// fonction qui free tout
			return (1);
		}
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
