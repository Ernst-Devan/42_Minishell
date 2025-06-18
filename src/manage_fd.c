/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:21:03 by njooris           #+#    #+#             */
/*   Updated: 2025/06/17 13:21:34 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "parsing.h"
#include "builtins.h"
#include "libft.h"
#include "exec.h"
#include "pipe.h"
#include "env_manage.h"
#include <signal.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

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
