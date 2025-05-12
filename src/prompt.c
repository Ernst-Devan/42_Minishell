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
		ft_strlcat(prompt, "\e[0;36m", PATH_MAX);
		ft_strlcat(prompt, find_env("PWD", shell->env), PATH_MAX);
		ft_strlcat(prompt, "\e[0;37m : (づ◕‿‿◕)づ🩵 \e[0;37m", PATH_MAX);
	}
	if (shell->error_code)
	{
		ft_strlcat(prompt, "\e[0;91m", PATH_MAX);
		ft_strlcat(prompt, find_env("PWD", shell->env), PATH_MAX);
		ft_strlcat(prompt, "\e[0;37m : (づಠ__ಠ)づ💢 \e[0;37m", PATH_MAX);
	}
	input = readline(prompt);
	if (!input)
	{
		free_lstr(shell->env);
		printf("exit\n");
		exit(0);
	}
	add_history(input);
	shell->error_code = 0;
	return (input);
}
