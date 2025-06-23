/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:55:59 by njooris           #+#    #+#             */
/*   Updated: 2025/06/23 13:17:22 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include "pipe.h"
#include "exec.h"
#include "libft.h"


void	manage_close_in_pipe(t_cmd command, int in, int pipefd[2])
{
	if (command.out != STDOUT_FILENO)
		close(command.out);
	if (command.in != STDIN_FILENO)
		close(command.in);
	if (in != STDIN_FILENO && in != command.in)
		close(in);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
}

int	waiter(pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		last_status;

	status = 0;
	pid = 0;
	while (pid > -1)
	{
		pid = wait(&status);
		if (pid == last_pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (last_status);
}

int	exit_pipe(int	pipefd[2], t_pack_pipe pp)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close_fd(pp.table);
	free_table(pp.table);
	free_lstr(pp.shell->env);
	exit(0);
}

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
		free_table(pp.table);
		free_lstr(pp.shell->env);
		close(in);
		exit_pipe(pipefd, pp);
	}
	if (in != STDIN_FILENO)
		close(in);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
}

void	reset_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

int	use_pipe(t_cmd command, int in, int pipefd[2], t_pack_pipe pp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		exit_pipe(pipefd, pp);
		return (perror("fork error in use pipe"), 1);
	}
	if (pid == 0)
	{
		if (!command.path)
			exit_pipe(pipefd, pp);
		manage_dup_pipe(command, pipefd, in, pp);
		if (command.type == 0)
		{
			reset_signals();
			execve(command.path, command.args, pp.shell->env);
			perror("Commande not found");
		}
		else
			exec_builtins(command, &pp.shell->env, pp.shell, pp.table, pipefd);
		close_fd(pp.table);
		free_table(pp.table);
		free_lstr(pp.shell->env);
		exit(1);
	}
	manage_close_in_pipe(command, in, pipefd); // a refaire
	return (pid);
}

int	ms_pipe(t_table table, t_shell *shell)
{
	t_pack_pipe	pack_pipe;
	size_t		i;
	int			pipefd[2];
	int			save_in;
	int			val_return;

	i = 0;
	pack_pipe.shell = shell;
	pack_pipe.table = table;
	pipefd[0] = table.cmds[0].in;
	while (i < table.cmd_len)
	{
		save_in = pipefd[0];
		if (i + 1 < table.cmd_len && pipe(pipefd) == -1)
			return (perror("pipe error"), 1);
		if (i + 1 == table.cmd_len)
			pipefd[1] = table.cmds[i].out;
		val_return = use_pipe(table.cmds[i], save_in, pipefd, pack_pipe);
		if (val_return == -1)
			return (1);
		i++;
	}
	return (waiter(val_return));
}
