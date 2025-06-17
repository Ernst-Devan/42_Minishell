/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/06/13 08:36:38 by dernst           ###   ########.fr       */
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
		if (quote == 0 && (i > 1 && input[i - 1] != '\x1E') && input[i] == '|')
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

t_table parsing(t_shell *shell) 
{
	t_table	table;
	char	*input;

	input = get_command(shell);
	input = manage_space(input);
	printf("before:%s\n", input);
	input = lexer(input);
	printf("after:%s\n", input);
	if (lexical_analyser(input) == 1)
	{
		free(input);
		table.cmd_len = 0;
		table.cmds = NULL;
		shell->error_code = 2;
		return (table);
	}
	input = manage_expand(input, *shell);
	if (init_table(&table, count_nb_cmd(input)))
		free_table(table);
	if (parser(&table, shell->env,input))
		free_table(table);
	return (table);
}
