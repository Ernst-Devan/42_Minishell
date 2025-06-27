/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:29 by njooris           #+#    #+#             */
/*   Updated: 2025/06/27 13:49:52 by dernst           ###   ########lyon.fr   */
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

char	**skip_redirection(char **split_cmd)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (check_empty(split_cmd) == 0)
	{
		free_lstr(split_cmd);
		return (NULL);
	}
	while (split_cmd[i])
	{
		temp = malloc((ft_strlen(split_cmd[i]) + 1) * sizeof(char));
		if (!temp)
		{
			free_lstr(split_cmd);
			return (NULL);
		}
		temp = skip_useless_redirections(split_cmd[i], temp);
		free(split_cmd[i]);
		split_cmd[i] = temp;
		i++;
	}
	return (split_cmd);
}

char	**manage_redirection(t_cmd **cmds, char **split_cmd)
{
	size_t	i;
	char	*in;
	char	*out;

	i = 0;
	if (!check_redirection(split_cmd))
		return (split_cmd);
	while (check_empty(split_cmd) == 1 && split_cmd[i])
	{
		if (init_redirection(&in, &out, split_cmd[i]))
			return (free_lstr_ret(split_cmd));
		manage_in_out_parse(split_cmd[i], &in, &out);
		(*cmds)[i].str_in = remove_quote(in);
		if (!(*cmds)[i].str_in)
			return (free_lstr_ret(split_cmd));
		(*cmds)[i++].str_out = remove_quote(out);
		if (!(*cmds)[i - 1].str_out)
		{
			free(out);
			return (free_lstr(split_cmd), NULL);
		}
	}
	return (skip_redirection(split_cmd));
}
