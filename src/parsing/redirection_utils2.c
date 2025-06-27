/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:22:17 by njooris           #+#    #+#             */
/*   Updated: 2025/06/27 13:44:42 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>

char	**free_manage_redirection(t_cmd **cmds, size_t i, char **split_cmd)
{
	free((*cmds)[i - 1].str_in);
	free_lstr(split_cmd);
	return (NULL);
}

char	**free_lstr_ret(char **split_cmd)
{
	free_lstr(split_cmd);
	return (NULL);
}

char	*skip_useless_redirections(char *split_cmd, char *temp)
{
	int		k;
	int		j;
	char	quote;

	j = 0;
	k = 0;
	quote = 0;
	while (split_cmd[j])
	{
		if (split_cmd[j] && split_cmd[j] == EXPAND)
			while (split_cmd[j] && split_cmd[++j] != EXPAND)
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

void	manage_in_out_parse(char *split_cmd, char **in, char **out)
{
	size_t		j;
	char		quote;

	j = 0;
	quote = 0;
	while (split_cmd[j])
	{
		if (split_cmd[j] && split_cmd[j] == EXPAND)
		{
			j++;
			while (split_cmd[j] && split_cmd[j] != EXPAND)
				j++;
		}
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
