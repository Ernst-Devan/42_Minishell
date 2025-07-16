/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dernst <dernst@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/07/16 14:18:03 by dernst           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include "pipe.h"
#include "exec.h"
#include "libft.h"

void	manage_dup_pipe(t_cmd command, int pipefd[2], int in, t_pack_pipe pp)
{
	if (pipefd[0] != STDIN_FILENO && pipefd[0] != in)
		close(pipefd[0]);
	if (command.in != STDIN_FILENO && in != command.in)
	{
		close(in);
		in = command.in;
	}
	if (command.out != STDOUT_FILENO && pipefd[1] != command.out)
	{
		close(pipefd[1]);
		pipefd[1] = command.out;
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1 || dup2(in, STDIN_FILENO) == -1)
	{
		perror("dup2 faild in usepipe");
		close(in);
		exit_pipe(pipefd, pp);
	}
	if (in != STDIN_FILENO)
		close(in);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
}

int	use_pipe(t_cmd command, int in, int pipefd[2], t_pack_pipe pp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_pipe(pipefd, pp);
	if (pid == 0)
	{
		if (!command.path)
		{
			close(in);
			exit_pipe(pipefd, pp);
		}
		manage_dup_pipe(command, pipefd, in, pp);
		if (command.type == 0 || command.type == 3)
		{
			reset_signals();
			execve(command.path, command.args, pp.shell->env);
			perror("Commande not found");
		}
		else
			exec_builtins(command, pp.shell, pp.table, pipefd);
		exit_pipe(pipefd, pp);
	}
	manage_close_in_pipe(command, in, pipefd);
	return (pid);
}

int	ms_pipe(t_table table, t_shell *shell)
{
	t_pack_pipe	pack_pipe;
	size_t		i;
	int			pipefd[2];
	int			save_in;
	int			val_return;

	i = -1;
	pack_pipe.shell = shell;
	pack_pipe.table = table;
	pipefd[0] = table.cmds[0].in;
	while (++i < table.cmd_len)
	{
		save_in = pipefd[0];
		if (i + 1 < table.cmd_len && pipe(pipefd) == -1)
			return (1);
		if (i + 1 == table.cmd_len)
			pipefd[1] = table.cmds[i].out;
		val_return = use_pipe(table.cmds[i], save_in, pipefd, pack_pipe);
		if (val_return == -1)
			return (1);
	}
	return (waiter(val_return));
}
