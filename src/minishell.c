
#include "minishell.h"
#include "parsing.h"
#include "libft.h"

void	minishell(char **env)
{
	t_cmd	*cmd;

	while (1)
    {
		cmd = parsing(env);
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

