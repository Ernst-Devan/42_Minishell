/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:53:49 by njooris           #+#    #+#             */
/*   Updated: 2025/05/26 14:39:34 by njooris          ###   ########.fr       */
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

int	open_heredoc(char *str, char **eof, char **name)
{
	int		n;
	char	*nb;
	static int i;

	n = 0;
	if (*name == NULL)
		i = 0;
	else
		free (*name);
	nb = ft_itoa(i);
	if (!nb)
		return (-1);
	*name = ft_strjoin(".EOF", nb);
	free(nb);
	if (!*name)
		return (-1);
	while (!access(*name, F_OK))
	{
		free(*name);
		i++;
		nb = ft_itoa(i);
		if (!nb)
			return (-1);
		*name = ft_strjoin(".EOF", nb);
		free(nb);
		if (!name)
			return (-1);
	}
	i++;
	while (str[n] && str[n] != SEPARATOR)
		n++;
	*eof = malloc(sizeof(char) * (n + 1));
	if (!*eof)
		return (-1);
	ft_strlcpy(*eof, str, n + 1);
	n = open(*name, O_CREAT | O_RDWR, 0600);
	return (n);
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

void	heredoc(int	fd, char *eof)
{
	char	*input;

	if (manage_ctrl_c_var(3) == 1)
		return ;
	input = readline("heredoc>");
	while (ft_strncmp(eof, input, ft_strlen(eof) && input && manage_ctrl_c_var(3) != 1))
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free (input);
		input = readline("heredoc>");
	}
	free (input);
}

int	open_in_heredoc_cmd(t_cmd *cmd, int *nb_files)
{
	int	i;
	int	fd;
	char	*eof;
	char	*name;

	eof = NULL;
	i = 0;
	fd = 0;
	name = NULL;
	while (cmd->str_in[i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i + 2] && cmd->str_in[i] == '<' && cmd->str_in[i + 1] == '<' && cmd->str_in[i + 2] == SEPARATOR)
		{
			if (fd)
				close(fd);
			fd = open_heredoc(&cmd->str_in[i + 3], &eof, &name);
			if (fd == -1)
			{
				free(eof);
				free(name);
				return (1);
			}
			(*nb_files)++;
			heredoc(fd, eof);
			free (eof);
			if (fd == -1)
				return (1);
			close(fd);
			fd = open_in_file(name);
			if (fd != -1)
				unlink(name);
		}
		i++;
	}
	free(name);
	cmd->in = fd;
	return (fd);
}

int	open_in_cmd(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->str_in[i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i] == '<')
		{
			if (cmd->str_in[i + 1] && cmd->str_in[i + 2] && cmd->str_in[i + 1] == '<' && cmd->str_in[i + 2] == SEPARATOR)
			{
				i+=2;
				fd = cmd->in;
			}
			else if (cmd->str_in[i + 1] && cmd->str_in[i + 1] == SEPARATOR)
			{
				fd = open_in_file(&cmd->str_in[i + 2]);
				if (fd == -1)
					return (-1);
			}
		}
		i++;
	}
	cmd->in = fd;
	return (fd);
}

int	manage_in(t_cmd *cmds, t_table table, int *nb_files)
{
	size_t		i;
	int		check;

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