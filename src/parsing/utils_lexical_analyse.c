/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexical_analyse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:10:46 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 13:47:37 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	quote_check(char *input)
{
	char	quote;
	size_t	j;

	j = 0;
	quote = 0;
	while (input[j])
	{
		inside_quote(input[j], &quote);
		j++;
	}
	if (quote)
		return (2);
	return (0);
}

int	choose_define(char *input, int *i, char quote)
{
	int	j;

	j = 0;
	if ((input[0] == '"' && input[1] == '"')
		|| (input[0] == '\'' && input[1] == '\''))
		return ((*i) += 2, ERROR);
	if (input[0] == '<' && input[1] == '<')
		return ((*i) += 2, LESSLESS);
	if (input[0] == '>' && input[1] == '>')
		return ((*i) += 2, GREATGREAT);
	if (input[0] == '<')
		return ((*i)++, LESS);
	if (input[0] == '>')
		return ((*i)++, GREAT);
	if (input[0] == '|' && quote == 0)
		return ((*i)++, PIPE);
	while (input[j] && input[j] != '|' && input[j] != '"' && input[j] != '\''
		&& input[j] != '<' && input[j++] != '>')
		(*i)++;
	return (CMD);
}
