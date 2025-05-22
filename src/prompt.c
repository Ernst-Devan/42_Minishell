#include <parsing.h>
#include <limits.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*get_command(char *input, t_shell *shell)
{
	char	prompt[PATH_MAX];

	ft_strlcpy(prompt, "\0", PATH_MAX);	

	if (!shell->error_code)
	{
		ft_strlcat(prompt, "\001\e[0;36m\002", PATH_MAX);
		ft_strlcat(prompt, find_env("PWD=", shell->env), PATH_MAX);
		ft_strlcat(prompt, "\001\e[0;37m\002 : (\001づ\002\001◕\002\001‿\002\001‿\002\001◕\002)\001づ\002\001🩵 \002\001\e[0;37m\002", PATH_MAX);
	}
	else
	{
		ft_strlcat(prompt, "\001\e[0;91m\002", PATH_MAX);
		ft_strlcat(prompt, find_env("PWD=", shell->env), PATH_MAX);
		ft_strlcat(prompt, "\001\e[0;37m\002 : (づಠ__ಠ)づ💢 \001\e[0;37m\002", PATH_MAX);
	}
	input = readline(prompt);
	if (!input)
	{
		free_lstr(shell->env);
		printf("exit\n");
		exit(0);
	}
	add_history(input);
	return (input);
}
