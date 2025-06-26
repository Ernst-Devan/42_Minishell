/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:27:53 by njooris           #+#    #+#             */
/*   Updated: 2025/06/26 13:02:47 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	free_lstr(char **lstr)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (lstr)
	{
		while (lstr[i])
		{
			temp = lstr[i];
			free(temp);
			i++;
		}
		free(lstr);
	}
	return (1);
}

void	free_cmds(t_table table)
{
	size_t	i;

	i = 0;
	while (i < table.cmd_len)
	{
		if (table.cmds[i].str_in)
		{
			free(table.cmds[i].str_in);
			table.cmds[i].str_in = NULL;
		}
		if (table.cmds[i].str_out)
		{
			free(table.cmds[i].str_out);
			table.cmds[i].str_out = NULL;
		}
		free(table.cmds[i].path);
		free_lstr(table.cmds[i].args);
		i++;
	}
	free(table.cmds);
	table.cmds = NULL;
}

void	free_table(t_table table)
{
	if (table.cmds)
	{
		free_cmds(table);
		table.cmds = NULL;
	}
	free(table.cmds);
}
