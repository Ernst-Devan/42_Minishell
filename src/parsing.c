/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/04/22 11:15:29 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <unistd.h>
#include "libft.h"
// DONT FORGOT TO ADD THE HEADER
// ERROR IN THIS CASE : $(NOT_VALID_ENV) | ls
// MANAGE IF NAME FILE ARE TWO LONG

// NOT JUST SPACE BE CAREFUL TO ALL delimiter
// SKIP THE SPACE BUT TOO ALL SPACE DELIMITER LIKE TAB etc
// IF PRECEDENT ERROR CODE FALSE SO MAKE THE MAN NOT HAPPY


char	*get_command(char *input, char **env)
{
	char	prompt[PATH_MAX];

	ft_strlcpy(prompt, "\0", PATH_MAX);	
	ft_strlcat(prompt, "\e[0;36m", PATH_MAX);
	ft_strlcat(prompt, find_env("PWD", env), PATH_MAX);
	ft_strlcat(prompt, "\e[0;37m : (づ｡◕‿‿◕｡)づ ➡️ \e[0;37m", PATH_MAX);
	input = readline(prompt);
	if (!input)
		exit(1);
	return (input);
}

t_table parsing(char **env) 
{
	t_table table;
	char	*input;

	input = (char *){0};

	input = get_command(input, env);
	input = skip_space(input);
	input = lexer(input, env);
	ft_printf("%s\n", input);
	if (!input)
		exit(1);
	if (init_table(&table, count_characters(input, "|")))
		free_table(table);
	if (parser(&table, env,input))
		free_table(table);
	return (table);
}
