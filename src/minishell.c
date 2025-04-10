
#include "minishell.h"
#include "parsing.h"
#include "libft.h"

void	minishell(char **env)
{
	t_table table;

	while (1)
    {
		table = parsing(env);
		//exec(command);
    }
}

int main(int ac, char **argv, char **env)
{
    (void)ac;
    (void)argv;
	minishell(env);
	return (0);
}

