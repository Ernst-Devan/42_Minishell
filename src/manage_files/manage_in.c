/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:53:49 by njooris           #+#    #+#             */
/*   Updated: 2025/06/19 17:07:44 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "exec.h"
#include <fcntl.h>

char	**try_access(char **name, int i)
{
	char	*nb;

	while (!access(*name, F_OK))
	{
		free(*name);
		i++;
		nb = ft_itoa(i);
		if (!nb)
			return (NULL);
		*name = ft_strjoin(".EOF", nb);
		free(nb);
		if (!name)
			return (NULL);
	}
	return (name);
}

int	open_in_file(char *str)
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
	n = open(new_str, O_RDONLY);
	free(new_str);
	return (n);
}

int	open_in_cmd(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (cmd->str_in && cmd->str_in[++i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i] == '<')
		{
			if (cmd->str_in[i + 1] && cmd->str_in[i + 2]
				&& cmd->str_in[i + 1] == '<' && cmd->str_in[i + 2] == SEPARATOR)
			{
				i += 2;
				fd = cmd->in;
			}
			else if (cmd->str_in[i + 1] && cmd->str_in[i + 1] == SEPARATOR)
			{
				fd = open_in_file(&cmd->str_in[i + 2]);
				if (fd == -1)
					return (-1);
			}
		}
	}
	cmd->in = fd;
	return (fd);
}

int	manage_in(t_cmd *cmds, t_table table, int *nb_files)
{
	size_t		i;
	int			check;

	check = 0;
	i = 0;
	while (i < table.cmd_len)
	{
		cmds[i].in = open_in_heredoc_cmd(&cmds[i], nb_files);
		i++;
	}
	i = 0;
	while (i < table.cmd_len)
	{
		check = open_in_cmd(&cmds[i]);
		if (check == -1)
		{
			cmds[i].in = -1;
			perror("Error in manage in");
			return (1);
		}
		cmds[i].out = 1;
		i++;
	}
	return (0);
}
