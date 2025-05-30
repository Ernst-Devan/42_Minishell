/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:55:44 by njooris           #+#    #+#             */
/*   Updated: 2025/05/21 13:35:13 by njooris          ###   ########.fr       */
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

int	open_append(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] && str[n] != SEPARATOR)
		n++;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, str, n + 1);
	n = open(new_str, O_CREAT | O_RDWR | O_APPEND, 0600);
	free(new_str);
	return (n);
}

int	open_out_file(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] && str[n] != SEPARATOR)
		n++;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, str, n + 1);
	n = open(new_str, O_CREAT | O_RDWR | O_TRUNC, 0600);
	free(new_str);
	return (n);
}

int	open_out_cmd(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->str_out[i])
	{
		if (cmd->str_out[i] && cmd->str_out[i + 1] && cmd->str_out[i] == '>')
		{
			if (cmd->str_out[i + 1] && cmd->str_out[i + 2] && cmd->str_out[i + 1] == '>' && cmd->str_out[i + 2] == SEPARATOR)
			{	
				fd = open_append(&cmd->str_out[i + 3]);
				i+=2;
			}
			else if (cmd->str_out[i + 1] && cmd->str_out[i + 1] == SEPARATOR)
			{
				fd = open_out_file(&cmd->str_out[i + 2]);
				if (fd == -1)
					return (-1);
			}
		}
		i++;
	}
	if (fd == 0)
		fd++;
	cmd->out = fd;
	return (fd);
}

int	manage_out(t_cmd *cmds, t_table table)
{
	size_t		i;
	int		check;

	i = 0;
	check = 1;
	while (i < table.cmd_len)
	{
		check = open_out_cmd(&cmds[i]);
		if (check == -1)
		{
			cmds[i].in = 0;
			perror("Error in manage in");
			return (1);
		}
		i++;
	}
	return (0);
}
