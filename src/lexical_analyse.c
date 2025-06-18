/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:45:56 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 13:21:15 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

#define CMD 0
#define LESSLESS 1
#define GREAT 2
#define PIPE 3
#define LESS 4
#define GREATGREAT 5
#define ERROR 6

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

int	*init_new_tab(int len, int define, int *tab)
{
	int	*new_tab;
	int	j;

	new_tab = malloc(sizeof(int) * (len + 1));
	if (!new_tab)
		return (NULL);
	j = 0;
	while (j < len)
	{
		new_tab[j] = tab[j];
		j++;
	}
	new_tab[len] = define;
	free(tab);
	tab = new_tab;
	return (tab);
}

int	*lexical_analyser_define(char *input, int *len)
{
	int		i;
	int		*tab;
	int		define;
	char	quote;

	i = 0;
	quote = 0;
	tab = NULL;
	while (input[i])
	{
		while (input[i] == SEPARATOR)
			i++;
		while (input[i] && inside_quote(input[i], &quote))
			i++;
		if (input[i])
		{
			define = choose_define(&input[i], &i, quote);
			tab = init_new_tab((*len)++, define, tab);
			if (!tab)
				return (NULL);
		}
	}
	return (tab);
}

int	check_lexical(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tab[0] == PIPE)
			return (1);
		if ((tab[i] == GREAT || tab[i] == GREATGREAT
				|| tab[i] == LESS || tab[i] == LESSLESS)
			&& (i + 1 == len || tab[i + 1] != CMD))
			return (1);
		if (tab[i] == PIPE && ((i + 1 == len)
				|| ((i + 1 < len && tab[i + 1] == PIPE))))
			return (1);
		i++;
	}
	return (0);
}

int	lexical_analyser(char *input)
{
	int		*tab;
	int		len;
	int		check;
	int		check_quote;

	len = 0;
	tab = lexical_analyser_define(input, &len);
	check = check_lexical(tab, len);
	check_quote = quote_check(input);
	free(tab);
	if (check == 1 || check_quote)
	{
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		return (1);
	}
	return (0);
}
