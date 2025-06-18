/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:01 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 11:28:04 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stddef.h>

void	init_cmd(t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (i < nb_cmd)
	{
		cmd[i].type = 0;
		cmd[i].path = NULL;
		cmd[i].args = NULL;
		cmd[i].in = 0;
		cmd[i].out = 1;
		cmd[i].str_in = NULL;
		cmd[i].str_out = NULL;
		i++;
	}
}

size_t	init_table(t_table *table, int nb_cmd)
{
	table->cmds = ft_calloc((nb_cmd + 1), sizeof(t_cmd));
	if (!table->cmds)
		return (1);
	table->cmd_len = nb_cmd;
	init_cmd(table->cmds, nb_cmd + 1);
	return (0);
}

size_t	init_expand(t_expand *expand, char *input, t_shell shell)
{
	size_t	alloc;

	alloc = size_allocation_expand(input, shell);
	expand->i = 0;
	expand->j = 0;
	expand->alloc = alloc;
	expand->buffer = ft_calloc(alloc + 1, sizeof(char));
	if (!expand->buffer)
		return (1);
	return (0);
}

