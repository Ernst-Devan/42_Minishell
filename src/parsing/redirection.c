/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:29 by njooris           #+#    #+#             */
/*   Updated: 2025/06/25 14:49:47 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>

char	*remove_quote(char *str)
{
	size_t	i;
	size_t	j;
	char	*temp;
	char	quote;

	if (!count_chars(str, "\"\'"))
		return (str);
	i = 0;
	j = 0;
	quote = 0;
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (str && str[i])
	{
		if (inside_quote(str[i], &quote) > 1 && i++)
		{
			if (str[i] && str[i] == quote && i++)
				quote = 0;
		}
		else
			temp[j++] = str[i++];
	}
	temp[j] = '\0';
	return (free(str), temp);
}

size_t	check_empty(char **lstr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (lstr[i])
	{
		while (lstr[i][j])
		{
			if (ft_isascii(lstr[i][j]) && lstr[i][j] != SEP)
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*useless_function5(char *split_cmd, char *temp)
{
	int		k;
	int		j;
	char	quote;

	j = 0;
	k = 0;
	quote = 0;
	while (split_cmd[j])
	{
		if (split_cmd[j] == EXPAND)
			while (split_cmd[++j] != EXPAND)
				temp[k++] = split_cmd[j];
		inside_quote(split_cmd[j], &quote);
		if (quote == 0 && (split_cmd[j] == '>' || split_cmd[j] == '<'))
		{
			j += ft_strlen_c(&split_cmd[j], SEP);
			if (split_cmd[j])
				j++;
			j += ft_strlen_c(&split_cmd[j], SEP);
		}
		if (split_cmd[j])
			temp[k++] = split_cmd[j++];
	}
	temp[k] = '\0';
	return (temp);
}

char	**skip_redirection(char **split_cmd)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (check_empty(split_cmd) == 0)
		return (free_lstr(split_cmd), NULL);
	while (split_cmd[i])
	{
		temp = malloc((ft_strlen(split_cmd[i]) + 1) * sizeof(char));
		if (!temp)
			return (NULL);
		temp = useless_function5(split_cmd[i], temp);
		free(split_cmd[i]);
		split_cmd[i] = temp;
		i++;
	}
	return (split_cmd);
}

void	useless_function6(char *split_cmd, char **in, char **out)
{
	size_t		j;
	char		quote;

	j = 0;
	quote = 0;
	while (split_cmd[j])
	{
		if (split_cmd[j] && split_cmd[j++] == EXPAND)
			while (split_cmd[j] != EXPAND)
				j++;
		inside_quote(split_cmd[j], &quote);
		if (quote == 0)
		{
			*in = redirection_in(*in, split_cmd, &j, &quote);
			*out = redirection_out(*out, split_cmd, &j, &quote);
		}
		if (!split_cmd[j])
			break ;
		j++;
	}
}

char	**manage_redirection(t_cmd **cmds, char **split_cmd)
{
	size_t	i;
	char	*in;
	char	*out;
	char	quote;

	i = 0;
	quote = 0;
	if (!check_redirection(split_cmd))
		return (split_cmd);
	while (check_empty(split_cmd) == 1 && split_cmd[i])
	{
		if (init_redirection(&in, &out, split_cmd[i]))
			return (free_lstr(split_cmd), NULL);
		useless_function6(split_cmd[i], &in, &out);
		(*cmds)[i].str_in = remove_quote(in);
		if (!(*cmds)[i].str_in)
			return (free_lstr(split_cmd), NULL);
		(*cmds)[i++].str_out = remove_quote(out);
		if (!(*cmds)[i - 1].str_out)
		{
			free((*cmds)[i - 1].str_in);
			return (free(split_cmd), NULL);
		}
	}
	return (skip_redirection(split_cmd));
}
