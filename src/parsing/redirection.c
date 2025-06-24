/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:29 by njooris           #+#    #+#             */
/*   Updated: 2025/06/24 16:53:00 by dernst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>

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
	while (str[i])
	{
		if (inside_quote(str[i], &quote) > 1)
		{
			i++;
			if (str[i] && str[i] == quote)
			{
				quote = 0;
				i++;
			}
		}
		else
			temp[j++] = str[i++];
	}
	temp[j] = '\0';
	free(str);
	return (temp);
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
	size_t	j;
	size_t	k;
	char	*temp;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	if (check_empty(split_cmd) == 0)
	{
		free_lstr(split_cmd);
		return (NULL);
	}
	while (split_cmd[i])
	{
		k = 0;
		temp = malloc((ft_strlen(split_cmd[i]) + 1) * sizeof(char));
		if (!temp)
			return (NULL);
		while (split_cmd[i][j])
		{
			if (split_cmd[i][j] == EXPAND)
			{
				temp[k++] = split_cmd[i][j++];
				while (split_cmd[i][j] != EXPAND)
					temp[k++] = split_cmd[i][j++];
			}
			inside_quote(split_cmd[i][j], &quote);
			if (quote == 0)
			{
				if (split_cmd[i][j] == '>' || split_cmd[i][j] == '<')
				{
					j += ft_strlen_c(&split_cmd[i][j], SEP);
					if (split_cmd[i][j])
						j++;
					j += ft_strlen_c(&split_cmd[i][j], SEP);
				}
			}
			if (!split_cmd[i][j])
				break ;
			temp[k] = split_cmd[i][j];
			k++;
			j++;
		}
		j = 0;
		temp[k] = '\0';
		free(split_cmd[i]);
		split_cmd[i] = temp;
		i++;
	}
	return (split_cmd);
}

char	**manage_redirection(t_cmd **cmds, char **split_cmd)
{
	size_t	i;
	size_t	j;
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
		{
			free_lstr(split_cmd);
			return (NULL);
		}
		j = 0;
		while (split_cmd[i][j])
		{
			if (split_cmd[i][j] == EXPAND)
			{
				j++;
				while (split_cmd[i][j] != EXPAND)
					j++;
			}
			inside_quote(split_cmd[i][j], &quote);
			if (quote == 0)
			{
				in = redirection_in(in, split_cmd[i], &j, &quote);
				out = redirection_out(out, split_cmd[i], &j, &quote);
			}
			if (!split_cmd[i][j])
				break ;
			j++;
		}
		(*cmds)[i].str_in = remove_quote(in);
		if (!(*cmds)[i].str_in)
		{
			free_lstr(split_cmd);
			return (NULL);
		}
		(*cmds)[i++].str_out = remove_quote(out);
		if (!(*cmds)[i - 1].str_out)
		{
			free(split_cmd);
			free((*cmds)[i - 1].str_in);
			return (NULL);
		}
	}
	return (skip_redirection(split_cmd));
}
