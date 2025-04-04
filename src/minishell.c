
#include "minishell.h"
#include "parsing.h"
#include "libft.h"

void	minishell(char **env)
{
	t_command command;

	while (1)
    {
		command = parsing(env);
        ft_printf("%s\n", command.path);
        ft_printf("%s", command.args[0]);

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

