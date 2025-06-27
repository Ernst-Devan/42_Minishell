/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:45:56 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 13:48:39 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"

int	*init_new_tab(int len, int define, int *tab, int *check)
{
	int	*new_tab;
	int	j;

	new_tab = ft_calloc((len + 1), sizeof(int));
	if (!new_tab)
	{
		*check = 1;
		return (NULL);
	}
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

size_t	lexical_analyser_define(char *input, int *len, int *check, int **tab)
{
	int		i;
	int		define;
	char	quote;
	int		is_word;

	i = 0;
	quote = 0;
	while (input[i])
	{
		is_word = 0;
		while (input[i] == SEP)
			i++;
		while (input[i] && inside_quote(input[i], &quote) && i++)
			is_word = 1;
		if (input[i] || is_word)
		{
			define = CMD;
			if (!(!input[i] && is_word))
				define = choose_define(&input[i], &i, quote);
			*tab = init_new_tab((*len)++, define, *tab, check);
			if (!*tab)
				return (E_MALLOC);
		}
	}
	return (0);
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

int	lexical(t_shell *shell, char **input, t_table **table)
{
	int	check;

	check = lexical_analyser(*input);
	if (check)
	{
		init_table(table, input, 0);
		free(*input);
		if (check == 2)
			shell->error_code = 2;
		return (check);
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
	check = 0;
	tab = NULL;
	if (lexical_analyser_define(input, &len, &check, &tab))
		return (E_MALLOC);
	if (!tab && check)
		return (1);
	check = check_lexical(tab, len);
	check_quote = quote_check(input);
	free(tab);
	if (check == 1 || check_quote)
	{
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		return (2);
	}
	return (0);
}
