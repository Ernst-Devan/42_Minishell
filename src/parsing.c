/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/06/18 13:42:26 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include "exec.h"

// DONT FORGOT TO ADD THE HEADER
// ERROR IN THIS CASE : $(NOT_VALID_ENV) | ls
// MANAGE IF NAME FILE ARE TWO LONG
  
// NOT JUST SPACE BE CAREFUL TO ALL delimiter
// SKIP THE SPACE BUT TOO ALL SPACE DELIMITER LIKE TAB etc
//

size_t	count_nb_pipe(char *input)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (input[i])
	{
		inside_quote(input[i], &quote);
		if (input[i] == SEP_TEXT)
		{
			i++;
			while (input[i] == '|')
			{
				i++;
			}
		}
		if (quote == 0 && input[i] == '|')
			count++;	
		i++;
	}
	return (count);
}

size_t	count_nb_cmd(char *input)
{
	size_t	nb_cmd;

	nb_cmd = count_nb_pipe(input);
	if (ft_strlen(input))
		nb_cmd++;
	return (nb_cmd);
}

size_t	parsing(t_shell *shell, t_table *table) 
{
	char	*input;
	size_t	lexical_check;

	input = get_command(shell);\
	input = manage_space(input);
	if (!input)
		return (1);
	input = lexer(input);
	if (! input)
		return (1);
	lexical_check = lexical_analyser(input);
	if (lexical_check)
	{
		free(input);
		if (lexical_check == 2)
			shell->error_code = 2;
		return (lexical_check);
	}
	input = manage_expand(input, *shell);
	if (!input)
		return (1);
	
	if (init_table(table, count_nb_cmd(input)))
	{
		free(input);
		return (1);
	}
	if (parser(table, shell->env,input))
	{
		free_table(*table);
		return (1);
	}
	return (0);
}
