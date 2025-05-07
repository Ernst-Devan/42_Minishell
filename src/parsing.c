/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/05/07 17:07:39 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
// DONT FORGOT TO ADD THE HEADER
// ERROR IN THIS CASE : $(NOT_VALID_ENV) | ls
// MANAGE IF NAME FILE ARE TWO LONG

// NOT JUST SPACE BE CAREFUL TO ALL delimiter
// SKIP THE SPACE BUT TOO ALL SPACE DELIMITER LIKE TAB etc
// IF PRECEDENT ERROR CODE FALSE SO MAKE THE MAN NOT HAPPY


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
	shell->error_code = 0;
	return (input);
}


t_table parsing(t_shell *shell) 
{
	t_table table;
	char	*input;

	input = (char *){0};

	input = get_command(input, shell);
	input = skip_space(input, &shell->error_code);
	input = lexer(input, shell->env);
	if (init_table(&table, count_split(input, '|')))
		free_table(table);
	if (parser(&table, shell->env,input))
		free_table(table);
	return (table);
}
