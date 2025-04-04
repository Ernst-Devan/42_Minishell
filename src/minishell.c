
#include "minishell.h"
#include "parse.h"

void	minishell(char **env)
{
	char	**data;

	while (1)
    {
		data = parse();
        exec(data);
    }
}

int main(int ac, char **argv, char **env)
{
	char	**parse;
    (void)ac;
    (void)argv;
	minishell(env);
	return (0);
}
