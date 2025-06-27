/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:24:05 by njooris           #+#    #+#             */
/*   Updated: 2025/06/19 16:17:59 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <readline/readline.h>
#include "libft.h"
#include "exec.h"

int	make_file_heredoc(char **eof, char **name, char *str, int n)
{
	*eof = malloc(sizeof(char) * (n + 1));
	if (!*eof)
		return (-1);
	ft_strlcpy(*eof, str, n + 1);
	n = open(*name, O_CREAT | O_RDWR, 0600);
	return (n);
}

void	heredoc(int fd, char *eof)
{
	char	*input;

	if (manage_ctrl_c_var(3) == 1)
		return ;
	input = readline("heredoc>");
	while (input && ft_strncmp(eof, input, ft_strlen(eof))
		&& manage_ctrl_c_var(3) != 1)
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free (input);
		input = readline("heredoc>");
	}
	free (input);
}

int	manage_heredoc(int fd, char *str_in)
{
	char	*eof;
	char	*name;

	eof = NULL;
	name = NULL;
	if (fd)
		close(fd);
	fd = open_heredoc(str_in, &eof, &name);
	if (fd == -1)
	{
		free(eof);
		free(name);
		return (-1);
	}
	heredoc(fd, eof);
	free (eof);
	if (fd == -1)
		return (-1);
	close(fd);
	fd = open_in_file(name);
	if (fd != -1)
		unlink(name);
	free(name);
	return (fd);
}

int	open_heredoc(char *str, char **eof, char **name)
{
	int			n;
	char		*nb;
	static int	i;

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
	name = try_access(name, i);
	i++;
	while (str[n] && str[n] != SEP)
		n++;
	n = make_file_heredoc(eof, name, str, n);
	return (n);
}

int	open_in_heredoc_cmd(t_cmd *cmd, int *nb_files)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->str_in && cmd->str_in[i])
	{
		if (cmd->str_in[i] && cmd->str_in[i + 1] && cmd->str_in[i + 2]
			&& cmd->str_in[i] == '<' && cmd->str_in[i + 1] == '<'
			&& cmd->str_in[i + 2] == SEP)
		{
			fd = manage_heredoc(fd, &cmd->str_in[i + 3]);
			if (fd == -1)
				return (-1);
			(*nb_files)++;
		}
		i++;
	}
	cmd->in = fd;
	return (fd);
}
