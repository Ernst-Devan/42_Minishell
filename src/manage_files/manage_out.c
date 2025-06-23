/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:55:44 by njooris           #+#    #+#             */
/*   Updated: 2025/06/19 17:09:50 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "exec.h"
#include <fcntl.h>

int	open_append(char *str)
{
	char	*new_str;
	int		n;

	n = 0;
	while (str[n] && str[n] != SEP)
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
	while (str[n] && str[n] != SEP)
		n++;
	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (-1);
	ft_strlcpy(new_str, str, n + 1);
	n = open(new_str, O_CREAT | O_RDWR | O_TRUNC, 0600);
	free(new_str);
	return (n);
}

int	manage_open_out(int i, t_cmd *cmd, int fd)
{
	if (cmd->str_out[i] && cmd->str_out[i + 1] && cmd->str_out[i] == '>')
	{
		if (cmd->str_out[i + 1] && cmd->str_out[i + 2]
			&& cmd->str_out[i + 1] == '>' && cmd->str_out[i + 2] == SEP)
		{
			if (fd)
				close(fd);
			fd = open_append(&cmd->str_out[i + 3]);
			if (fd == -1)
				return (-1);
			i += 2;
		}
		else if (cmd->str_out[i + 1] && cmd->str_out[i + 1] == SEP)
		{
			if (fd)
				close(fd);
			fd = open_out_file(&cmd->str_out[i + 2]);
			if (fd == -1)
				return (-1);
		}
	}
	return (fd);
}

int	open_out_cmd(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->str_out && cmd->str_out[i])
	{
		fd = manage_open_out(i, cmd, fd);
		if (fd == -1)
			return (-1);
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
	int			check;

	i = 0;
	check = 1;
	while (manage_ctrl_c_var(3) != 1 && i < table.cmd_len)
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
