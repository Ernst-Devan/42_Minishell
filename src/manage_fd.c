/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:21:03 by njooris           #+#    #+#             */
/*   Updated: 2025/06/18 11:15:41 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing.h"

void	close_fd(t_table table)
{
	size_t	i;

	i = 0;
	while (i < table.cmd_len)
	{
		if (table.cmds[i].in != 0)
			close(table.cmds[i].in);
		if (table.cmds[i].out != 1)
			close(table.cmds[i].out);
		i++;
	}
}
