/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:19 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 15:54:03 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <limits.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*get_command(t_shell *shell)
{
	char	prompt[PATH_MAX];
	char	*input;

	ft_strlcpy(prompt, "\0", PATH_MAX);
	if (!shell->error_code)
	{
		ft_strlcat(prompt, RED, PATH_MAX);
		ft_strlcat(prompt, find_env("PWD=", shell->env), PATH_MAX);
		ft_strlcat(prompt, WHITE" : "WHITE, PATH_MAX);
	}
	else
	{
		ft_strlcat(prompt, BLUE, PATH_MAX);
		ft_strlcat(prompt, find_env("PWD=", shell->env), PATH_MAX);
		ft_strlcat(prompt, WHITE " : " WHITE, PATH_MAX);
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
