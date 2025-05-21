/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:45:56 by njooris           #+#    #+#             */
/*   Updated: 2025/05/21 12:31:10 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

#define CMD 0
#define LESSLESS 1
#define GREAT 2
#define PIPE 3
#define LESS 4
#define GREATGREAT 5
#define ERROR 6

int	choose_define(char *input, int *i)
{
	int	j;

	j = 0;
	if ((input[0] == '"' && input[1] == '"') || (input[0] == '\'' && input[0] == '\''))
	{
		(*i) += 2;
		return (ERROR);
	}
	if (input[0] == '<' && input[1] == '<')
	{
		(*i) += 2;
		return (LESSLESS);
	}
	if (input[0] == '>' && input[1] == '>')
	{
		(*i) += 2;
		return (GREATGREAT);
	}
	if (input[0] == '<')
	{
		(*i)++;
		return (LESS);
	}
	if (input[0] == '>')
	{
		(*i)++;
		return (GREAT);
	}
	if (input[0] == '|')
	{
		(*i)++;
		return (PIPE);
	}
	while (input[j] && input[j] != '|' && input[j] != '<' && input[j] != '>')
	{
		j++;
		(*i)++;
	}
	return (CMD);
}

int	*lexical_analyser_define(char *input, int *len)
{
	int		i;
	int		*tab;
	int		define;
	int		*new_tab;
	int		j;

	i = 0;
	*len = 0;
	tab = NULL;
	while (input[i])
	{
		while (input[i] == ':')
			i++;
		if (input[i])
		{
			if ((input[0] == '"' && input[1] == '"') || (input[0] == '\'' && input[1] == '\''))
				i += 2;
			define = choose_define(&input[i], &i);
			new_tab = malloc(sizeof(int) * (*len + 1));
			j = 0;
			while (j < *len)
			{
				new_tab[j] = tab[j];
				j++;
			}
			new_tab[*len] = define;
			free(tab);
			tab = new_tab;
			(*len)++;
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
		if ((tab[i] == GREAT || tab[i] == GREATGREAT || tab[i] == LESS || tab[i] == LESSLESS)
			&& (i + 1 == len || tab[i + 1] != CMD))
			return (1);
		if (tab[i] == PIPE && (i + 1 < len && tab[i + 1] == PIPE))
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

	tab = lexical_analyser_define(input, &len);
	check = check_lexical(tab, len);
	if (check == 1)
		printf("syntax error\n");
	return (check);
}