/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:14:05 by dernst            #+#    #+#             */
/*   Updated: 2025/06/20 12:47:33 by njooris          ###   ########.fr       */
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
		if (input[i] == EXPAND)
		{
			i++;
			while (input[i] != EXPAND)
				i++;
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
	int		check;

	get_command(shell, &input);
	if (manage_space(&input))
		return (1);
	if (lexer(&input))
		return (1);
	check = lexical_analyser(input);
	if (check)
	{
		init_table(table, 0);
		free(input);
		if (check == 2)
			shell->error_code = 2;
		return (check);
	}
	if (manage_expand(*shell, &input) == 2)
		return (1);
	if (init_table(table, count_nb_cmd(input)))
	{
		free(input);
		return (1);
	}
	if (parser(table, shell->env, input))
	{
		free_table(*table);
		return (1);
	}
	return (0);
}
